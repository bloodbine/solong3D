/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:37:29 by gpasztor          #+#    #+#             */
/*   Updated: 2023/08/20 11:03:10 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	parse_error(char *error_message)
{
	write(STDERR_FILENO, "Error\n", 7);
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
	write(STDERR_FILENO, "\n", 2);
	exit(EXIT_FAILURE);
}

uint32_t	rgbtohex(int r, int g, int b, int a)
{
	return (((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8) \
	+ (a & 0xff));
}
