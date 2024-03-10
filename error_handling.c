/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlom <dlom@student.42prague.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:55:02 by dlom              #+#    #+#             */
/*   Updated: 2024/03/10 10:58:06 by dlom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redlomshell.h"

void	print_error(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}
