/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:38:40 by ffederol          #+#    #+#             */
/*   Updated: 2023/09/14 21:46:10 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "vector.h"

// Dir: N = (0|1), O = (1|0), S = (0|-1), W = (-1|0)
typedef struct s_player
{
	t_float_vector		pos;
	t_float_vector		dir; // N = (0|1), O = (1|0), S = (0|-1), W = (-1|0)
	t_float_vector		cam_plane;
	int					hp;
}			t_player;

#endif