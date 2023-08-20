/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:38:40 by ffederol          #+#    #+#             */
/*   Updated: 2023/08/20 11:03:40 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "vector.h"

typedef struct	s_parse
{
	char			*textures[5]; //{./path_to_the_north_texture,./path_to_the_east_texture,./path_to_the_s_texture,./path_to_the_w_texture,./path_to_the_door_texture, NULL}
	char			**worldMap;
	uint32_t		floor;
	uint32_t		roof;
	t_int_vector	playerPos;
	t_int_vector	playerDir; // (x|y)  N = (0|-1), O = (1|0), S = (0|1), W = (-1|0)
}				t_parse;

t_parse		*parse(int argc, char **argv);
void		parse_error(char *error_message);
uint32_t	rgbtohex(int r, int g, int b, int a);

#endif