/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redlomshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlom <dlom@student.42prague.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:51:07 by dlom              #+#    #+#             */
/*   Updated: 2024/02/04 00:58:23 by dlom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redlomshell.h"

int main(int argc, char **argv, char **env)
{
	char *input;
	char prompt[] = "minishell$ ";

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
		if (ft_strlen(input) > 0) {
			add_history(input);
		}

        // Echo the input back to the user
		ft_printf("You entered: %s\n", input);

		// Free the allocated memory
		free(input);
	}

	return 0;
}