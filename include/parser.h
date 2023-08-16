/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:38:40 by ffederol          #+#    #+#             */
/*   Updated: 2023/08/16 20:03:36 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "vector.h"

typedef struct	s_parse
{
	char			**textures; //{./path_to_the_north_texture,./path_to_the_east_texture,./path_to_the_s_texture,./path_to_the_w_texture,./path_to_the_door_texture, NULL}
	char			**worldMap; // or int[][]
	t_int_vector	playerPos;
	t_int_vector	playerDir; // (x|y)  N = (0|-1), O = (1|0), S = (0|1), W = (-1|0)
	uint32_t		floor;
	uint32_t		ceiling;
}				t_parse;

#endif