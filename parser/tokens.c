/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlom <dlom@student.42prague.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 22:36:34 by dlom              #+#    #+#             */
/*   Updated: 2024/02/18 22:37:21 by dlom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *whitespace = " \t\r\n";
char *symbols = "|();&<>";

int gettoken(char **ps, char *es, char **q, char **eq)
{
	char *s;
	int ret;

	s = *ps;
	while (s < es && strchr(whitespace, *s))
		s++;
	if (q)
		*q = s;
	ret = *s;

	if (*s == 0) {
	} else if (*s == '|' || *s == '(' || *s == ')' || *s == ';' || *s == '&' || *s == '<') {
		s++;
	} else if (*s == '>') {
		s++;
		if (*s == '>') {
			ret = '+';
			s++;
		}
	} else {
		ret = 'a';
		while (s < es && !strchr(whitespace, *s) && !strchr(symbols, *s))
			s++;
	}

	if (eq)
		*eq = s;

	while (s < es && strchr(whitespace, *s))
		s++;
	*ps = s;
	return ret;
}