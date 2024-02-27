/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redlomshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlom <dlom@student.42prague.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:51:07 by dlom              #+#    #+#             */
/*   Updated: 2024/02/27 01:00:06 by dlom             ###   ########.fr       */
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

int main(void)
{
	char *input;
	t_command command; // Assume this is your command structure

	setup_signals();

	while (1)
	{
		// readline gets a line from a user and returns it. The line is allocated withh malloc.
		// the final newline "/n" is removed.
		input = readline("minishell$ ");
		if (!input)
			break; // Exit if Ctrl-D is pressed

		if (*input)
			add_history(input); // Only add non-empty commands to history

		// // Parse the input to fill your command structure
		// parse_input(input, &command);

		// // Execute the command
		// execute_command(&command);

		// // Cleanup
		// free(input);
		// clear_command_structure(&command); // Assume this function clears your command structure
	}

    // Perform any final cleanup if necessary
    return 0;
}
