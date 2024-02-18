/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlom <dlom@student.42prague.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 22:36:34 by dlom              #+#    #+#             */
/*   Updated: 2024/02/18 23:08:11 by dlom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	gettoken(char **ps, char *es, char **q, char **eq)
{
	char	*s; // Pointer to navigate through the string
	int		ret; // Variable to hold the token type or character

	s = *ps; // Start at the current position in the string
	// Skip initial whitespace characters
	while (s < es && (*s == ' ' || *s == '\t' || *s == '\n'))
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
		while (s < es && !(*s == ' ' || *s == '\t' || *s == '\n') 
			&& !(*s == '|' || *s == '(' || *s == ')' || *s == ';'
				|| *s == '&' || *s == '<' || *s == '>'))
			s++;
	}
	if (eq) // If an end pointer for the token is provided
		*eq = s; // Set it to the current position
	// Skip any trailing whitespace after the token
	while (s < es && (*s == ' ' || *s == '\t' || *s == '\n'))
		s++;
	*ps = s; // Update the start position to the new position for next call
	return (ret); // Return the token type or character
}
