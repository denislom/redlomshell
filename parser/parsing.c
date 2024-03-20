/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlom <dlom@student.42prague.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:42:53 by dlom              #+#    #+#             */
/*   Updated: 2024/03/20 20:45:00 by dlom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../redlomshell.h"

t_cmd	*parse_cmd(char *s)
{
	char *es;
	t_cmd	*cmd;

	es = s + ft_strlen(s);
	cmd = parse_line(&s, es);
	peek(&s, es, "");
	if(s != es){
		write(STDERR_FILENO, "s != es\n", 8);
		exit(2);
	}
	nul_terminate(cmd);
	return cmd;
}

t_cmd	*parse_line(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = parse_pipe(ps, es);
	while(peek(ps, es, "&"))
	{
		get_token(ps, es, 0, 0);
		cmd = back_cmd(cmd);
	}
	if(peek(ps, es, ";"))
	{
		get_token(ps, es, 0, 0);
		cmd = list_cmd(cmd, parse_line(ps, es));
	}
	return cmd;
}

t_cmd	*parse_pipe(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = parse_exec(ps, es);
	if(peek(ps, es, "|"))
	{
		get_token(ps, es, 0, 0);
		cmd = pipe_cmd(cmd, parse_pipe(ps, es));
	}
	return cmd;
}


int	get_token(char **ps, char *es, char **q, char **eq)
{
	char	*s; // Pointer to navigate through the string
	int		ret; // Variable to hold the token type or character

	s = *ps; // Start at the current position in the string
	// Skip initial whitespace characters
	while (s < es && (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n' || *s == '\v'))
		s++;
	if (q) // If a start pointer for the token is provided
		*q = s; // Set it to the current position
	ret = *s; // Set the return value to the current character (token type)
	// Check for end of string
	if (*s == 0)
	{
		// Do nothing if at end of string
	}
	// Check for one-character tokens (operators and special symbols)
	else if
	(*s == '|' || *s == '(' || *s == ')' || *s == ';' || *s == '&' || *s == '<')
		s++; // Simply move past this character
	// Check for redirection token ('>')
	else if (*s == '>')
	{
		s++; // Move past '>'
		if (*s == '>') // If the next character is also '>', it's an append redirection
		{
			ret = '+'; // Use '+' to denote append redirection ('>>')
			s++; // Move past the second '>'
		}
	}
	// Handle argument tokens (not operators or whitespace)
	else
	{
		ret = 'a'; // Use 'a' to denote an argument token
		// Move past the characters of the token until hitting whitespace or a special symbol
		while (s < es && !(*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n' || *s == '\v') 
			&& !(*s == '|' || *s == '(' || *s == ')' || *s == ';'
				|| *s == '&' || *s == '<' || *s == '>'))
			s++;
	}
	if (eq) // If an end pointer for the token is provided
		*eq = s; // Set it to the current position
	// Skip any trailing whitespace after the token
	while (s < es && (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n' || *s == '\v'))
		s++;
	*ps = s; // Update the start position to the new position for next call
	return (ret); // Return the token type or character
}

/* 
Function peek non zero value (truthy value) if the next non white-space character
is one of the chars from toks.
*/

int	peek(char **ps, char *es, char *toks)
{
	char	*s;

	s = *ps;
	while (s < es && (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n' || *s == '\v'))
		s++;
	*ps = s;
	return (*s && ft_strchr(toks, *s));
}

t_cmd	*nul_terminate(t_cmd *cmd)
{
	int i = 0;
	t_backcmd *bcmd;
	t_execcmd *ecmd;
	t_listcmd *lcmd;
	t_pipecmd *pcmd;
	t_redircmd *rcmd;

	if(cmd == 0)
		return 0;

	if(cmd->type == EXEC)
	{
		ecmd = (t_execcmd*)cmd;
		while(ecmd->argv[i])
		{
			*ecmd->eargv[i] = 0;
			i++;
		}
	}
	else if(cmd->type == REDIR){
		rcmd = (t_redircmd*)cmd;
		nul_terminate(rcmd->cmd);
		*rcmd->efile = 0;
	}
	else if(cmd->type == PIPE)
	{
		pcmd = (t_pipecmd*)cmd;
		nul_terminate(pcmd->left);
		nul_terminate(pcmd->right);
	}
	else if(cmd->type == LIST)
	{
		lcmd = (t_listcmd*)cmd;
		nul_terminate(lcmd->left);
		nul_terminate(lcmd->right);
	}
	else if(cmd->type == BACK){
		bcmd = (t_backcmd*)cmd;
		nul_terminate(bcmd->cmd);
	}

	return cmd;
}

t_cmd	*parse_exec(char **ps, char *es)
{
	char			*q;
	char			*eq;
	int				tok;
	int				argc;
	t_execcmd		*cmd;
	t_cmd			*ret;

	if(peek(ps, es, "("))
		return (parse_block(ps, es));

	ret = exec_cmd();
	cmd = (t_execcmd*)ret;

	argc = 0;
	ret = parse_redirs(ret, ps, es);
	while(!peek(ps, es, "|)&;"))
	{
		if((tok=get_token(ps, es, &q, &eq)) == 0)
			break;
		if(tok != 'a')
			perror("syntax");
		cmd->argv[argc] = q;
		cmd->eargv[argc] = eq;
		argc++;
		if(argc >= MAXARGS)
			perror("too many args");
		ret = parse_redirs(ret, ps, es);
	}
	cmd->argv[argc] = 0;
	cmd->eargv[argc] = 0;
	return (ret);
}

t_cmd	*parse_block(char **ps, char *es)
{
	t_cmd	*cmd;

	if(!peek(ps, es, "("))
		perror("parse_block");
	get_token(ps, es, 0, 0);
	cmd = parse_line(ps, es);
	if(!peek(ps, es, ")"))
		perror("syntax - missing )");
	get_token(ps, es, 0, 0);
	cmd = parse_redirs(cmd, ps, es);
	return (cmd);
}

t_cmd	*parse_redirs(t_cmd *cmd, char **ps, char *es)
{
	int		tok;
	char	*q;
	char	*eq;

	while(peek(ps, es, "<>"))
	{
		tok = get_token(ps, es, 0, 0);
		if(get_token(ps, es, &q, &eq) != 'a')
			perror("missing file for redirection");
		
		if(tok == '<')
			cmd = redir_cmd(cmd, q, eq, O_RDONLY, 0);
		else if(tok == '>')
			cmd = redir_cmd(cmd, q, eq, O_WRONLY | O_CREAT, 1);
		else if(tok == '+') { // For '>>', assuming '+' represents it in your original code. Adjust as necessary.
			cmd = redir_cmd(cmd, q, eq, O_WRONLY | O_CREAT, 1); // Added O_APPEND for the append operation
		}
	}
	return cmd;
}
