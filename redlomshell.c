/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redlomshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlom <dlom@student.42prague.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:51:07 by dlom              #+#    #+#             */
/*   Updated: 2024/03/20 21:35:54 by dlom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redlomshell.h"

void handle_sigint(int sig)
{
	// Print a new line and the prompt again, do not exit the shell
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void setup_signals(void)
{
	signal(SIGINT, handle_sigint); // Handle Ctrl-C
	// Ignore SIGQUIT signal with Ctrl-\ signal(SIGQUIT, SIG_IGN);
}

int	get_cmd(char **input)
{
	char	cwd[PATH_MAX];
	char	*username = getenv("USER");

	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror("getcwd");
		return -1;
	}
	write(STDOUT_FILENO, username, strlen(username));
	write(STDOUT_FILENO, "@", 1);
	write(STDOUT_FILENO, "system", strlen("system"));
	write(STDOUT_FILENO, ":", 1);
	write(STDOUT_FILENO, cwd, strlen(cwd));
	write(STDOUT_FILENO, "$ ", 2);
	*input = readline(NULL);
	if (!*input)
		return -1;
	if (**input)
		add_history(*input);
	return (0);
}

int	fork1(void)
{
	int	pid;

	pid = fork();
	if(pid == -1)
		perror("fork");
	return pid;
}

int main(void)
{
	char	*input;
	int		fd;
	t_cmd	*parsed;

	input = NULL;
	parsed = NULL;
	setup_signals();
	// Ensure that three file descriptors are open.
	while((fd = open("console", O_RDWR)) >= 0)
	{
		if(fd >= 3)
		{
			close(fd);
			break;
		}
	}
	while(get_cmd(&input) >= 0)
	{
		if (ft_strncmp(input, "cd ", 3) == 0)
		{
			// Chdir must be called by the parent, not the child
			if (chdir(input + 3) == -1)
			{
				printf("bash: cd: %s: No such file or directory\n", (input + 3));
			}
			continue;
		}
		if (fork1() == 0)
		{
			parsed = parse_cmd(input);
			printf("from fork1: %d\n", parsed->type);
			// run_cmd(parsed);
			// run_cmd(parse_cmd(input));
		}
		wait(NULL);
	}
	printf("from main: %d\n", parsed->type);
	// Free the dynamically allocated inputfer at the end
	free(input);
	return 0;
}
