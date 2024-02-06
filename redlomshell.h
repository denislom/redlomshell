/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redlomshell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlom <dlom@student.42prague.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 00:18:00 by dlom              #+#    #+#             */
/*   Updated: 2024/02/06 22:32:31 by dlom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  REDLOMSHELL_H
# define REDLOMSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
# include "./libft/libft.h"

typedef struct s_simple_command
{
	char **args; // Array of strings for arguments, including the command as args[0]
} t_simple_command;

typedef struct s_command
{
	t_simple_command **simple_commands; // Array of simple commands
	char *infile;
	char *outfile;
	int append; // Boolean indicating if output redirection should append
	int background; // Boolean indicating if the command should run in the background
} t_command;


#define MAX_INPUT_SIZE 1024

#endif