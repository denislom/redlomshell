/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlom <dlom@student.42prague.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:02:21 by dlom              #+#    #+#             */
/*   Updated: 2024/03/11 22:25:03 by dlom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../redlomshell.h"

void
runcmd(t_cmd *cmd)
{
	int			p[2];
	t_backcmd		*bcmd;
	t_execcmd		*ecmd;
	t_listcmd		*lcmd;
	t_pipecmd		*pcmd;
	t_redircmd		*rcmd;

	if(cmd == 0)
		exit(NULL);

	if(cmd->type == EXEC)
	{
		ecmd = (t_execcmd*)cmd;
		if(ecmd->argv[0] == 0)
		exit(NULL);
		exec(ecmd->argv[0], ecmd->argv);
		printf(2, "exec %s failed\n", ecmd->argv[0]);
	}
	else if(cmd->type == REDIR)
	{
		rcmd = (struct redircmd*)cmd;
		close(rcmd->fd);
		if(open(rcmd->file, rcmd->mode) < 0)
		{
			printf(2, "open %s failed\n", rcmd->file);
			exit(NULL);
		}
		runcmd(rcmd->cmd);
	}
	else if(cmd->type == LIST)
	{
		lcmd = (struct listcmd*)cmd;
		if(fork1() == 0)
			runcmd(lcmd->left);
		wait(NULL);
		runcmd(lcmd->right);
	}
	else if(cmd->type == PIPE)
	{
		pcmd = (struct pipecmd*)cmd;
		if(pipe(p) < 0)
			perror("pipe");
		if(fork1() == 0)
		{
			close(1);
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->left);
		}
		if(fork1() == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->right);
		}
		close(p[0]);
		close(p[1]);
		wait(NULL);
		wait(NULL);
	}
	else if(cmd->type == BACK)
	{
		bcmd = (struct backcmd*)cmd;
		if(fork1() == 0)
			runcmd(bcmd->cmd);
	}
	else
		perror("runcmd");
	exit(NULL);
}

/* void
runcmd(struct cmd *cmd)
{
  int p[2];
  struct backcmd *bcmd;
  struct execcmd *ecmd;
  struct listcmd *lcmd;
  struct pipecmd *pcmd;
  struct redircmd *rcmd;

  if(cmd == 0)
    exit();

  if(cmd->type == EXEC) {
    ecmd = (struct execcmd*)cmd;
    if(ecmd->argv[0] == 0)
      exit();
    exec(ecmd->argv[0], ecmd->argv);
    printf(2, "exec %s failed\n", ecmd->argv[0]);
  }
  else if(cmd->type == REDIR) {
    rcmd = (struct redircmd*)cmd;
    close(rcmd->fd);
    if(open(rcmd->file, rcmd->mode) < 0){
      printf(2, "open %s failed\n", rcmd->file);
      exit();
    }
    runcmd(rcmd->cmd);
  }
  else if(cmd->type == LIST) {
    lcmd = (struct listcmd*)cmd;
    if(fork1() == 0)
      runcmd(lcmd->left);
    wait();
    runcmd(lcmd->right);
  }
  else if(cmd->type == PIPE) {
    pcmd = (struct pipecmd*)cmd;
    if(pipe(p) < 0)
      panic("pipe");
    if(fork1() == 0){
      close(1);
      dup(p[1]);
      close(p[0]);
      close(p[1]);
      runcmd(pcmd->left);
    }
    if(fork1() == 0){
      close(0);
      dup(p[0]);
      close(p[0]);
      close(p[1]);
      runcmd(pcmd->right);
    }
    close(p[0]);
    close(p[1]);
    wait();
    wait();
  }
  else if(cmd->type == BACK) {
    bcmd = (struct backcmd*)cmd;
    if(fork1() == 0)
      runcmd(bcmd->cmd);
  }
  else {
    panic("runcmd");
  }
  exit();
}
 */