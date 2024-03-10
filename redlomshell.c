/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redlomshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlom <dlom@student.42prague.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:51:07 by dlom              #+#    #+#             */
/*   Updated: 2024/03/10 22:29:24 by dlom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redlomshell.h"
#include <linux/limits.h>

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

int main(void)
{
	char	*input;

	input = NULL;
	setup_signals();

	while(get_cmd(&input) >= 0)
	{
		if (ft_strncmp(input, "cd ", 3) == 0)
		{
			// Chdir must be called by the parent, not the child
			if (chdir(input + 3) == -1)
			{
				printf("bash: cd: %s: No such file or directory\n", (input+3));
			}
			// if (chdir(input + 3) < 0)
			// {
			// 	printf(2, "cannot cd %s\n", input+3);
			// }
			continue;
		}
		// if (fork1() == 0) { // Assuming fork1 is your version of fork that handles errors
		// 	run_cmd(parse_cmd(input));
		// 	exit(0); // Ensure the child exits after running the command
		// }
		// wait(NULL); // Use wait with NULL to wait for any child process
	}

	// Free the dynamically allocated inputfer at the end
	free(input);
	return 0;
}
