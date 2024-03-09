/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redlomshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlom <dlom@student.42prague.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:51:07 by dlom              #+#    #+#             */
/*   Updated: 2024/03/09 23:13:48 by dlom             ###   ########.fr       */
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
	*input = readline("$ ");

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
		if (strncmp(input, "cd ", 3) == 0) {
			// Chdir must be called by the parent, not the child
			if (chdir(input + 3) < 0)
				fprintf(stderr, "cannot cd %s\n", input + 3); // Use fprintf for stderr
			continue;
		}
		if (fork1() == 0) { // Assuming fork1 is your version of fork that handles errors
			run_cmd(parse_cmd(input));
			exit(0); // Ensure the child exits after running the command
		}
		wait(NULL); // Use wait with NULL to wait for any child process
	}

	// Free the dynamically allocated inputfer at the end
	free(input);
	return 0;
}
