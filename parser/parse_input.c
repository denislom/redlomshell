/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlom <dlom@student.42prague.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 00:45:28 by dlom              #+#    #+#             */
/*   Updated: 2024/02/07 01:03:12 by dlom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../redlomshell.h"

/* 
<command_line> ::= <command_sequence> <background>?
<background> ::= '&'

<command_sequence> ::= <command> | <command_sequence> ';' <command> | <command_sequence> '&&' <command> | <command_sequence> '||' <command>
<command> ::= <simple_command> | <pipeline>
<pipeline> ::= <simple_command> '|' <pipeline>

<simple_command> ::= <redirection>* <executable> <arguments>* <redirection>*
<redirection> ::= '<' <filename> | '>' <filename> | '>>' <filename> | '2>' <filename>

<executable> ::= <word>
<arguments> ::= <word>+
<filename> ::= <word>

<word> ::= <non_space_sequence> | '"' <any_sequence> '"' | "'" <any_sequence> "'"
<non_space_sequence> ::= <any_character_except_space>+
<any_sequence> ::= <any_character>*
 */

void parse_input(char *input, t_command *command)
{
    // Tokenization process
    // Example: split input into tokens using spaces and special characters as delimiters

    // Syntax analysis
    // Example: for each token, determine its type and fill the `t_command` structure

    // Note: Implement specific functions to handle redirections, pipes, and command execution logic
}

char **tokenize(char *input) {
    // Split the input into tokens based on spaces and special characters
    // You might use strtok, strsep, or write your own splitter function
}

t_command *parse_tokens(char **tokens) {
    // Create a command structure from tokens
    // Identify pipes and redirections and organize commands and arguments accordingly
}
