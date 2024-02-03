// This will not be submitted to intra.

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
// cc test.c -lreadline

int main(int argc, char **argv, char **env)
{
	char *input;
	char prompt[] = "minishell> ";

// Main loop
	while (1) {
		// Get input from user
		input = readline(prompt);
	}
	return 0;
}