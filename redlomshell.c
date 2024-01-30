/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redlomshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlom <dlom@student.42prague.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:51:07 by dlom              #+#    #+#             */
/*   Updated: 2024/01/30 21:54:03 by dlom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redlomshell.h"

/* 
Prompt:
	denis@ubuntu:~$ == denis@ubuntu:/home/denis
	[username]@[name_of_system]:[current working directory of the shell]
	~: home directory /home/denis
	$: end of the prompt
 */

int main() {
	char *input;
	char prompt[] = "minishell> ";

// Main loop
	while (1) {
		// Get input from user
		input = readline(prompt);

		// Check for EOF (Ctrl+D)
		if (!input) {
			printf("\nExiting minishell.\n");
			break;
			}

		// Add input to history
		if (strlen(input) > 0) {
			add_history(input);
		}

        // Echo the input back to the user
		printf("You entered: %s\n", input);

		// Free the allocated memory
		free(input);
	}

	return 0;
}