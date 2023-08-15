/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:38:40 by ffederol          #+#    #+#             */
/*   Updated: 2023/08/14 18:40:58 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "vector.h"

typedef struct s_player 
{
	t_double_vector		*pos;
	t_double_vector		*dir; // N = (0|1), O = (1|0), S = (0|-1), W = (-1|0)
	t_double_vector		*cam_plane;
	int					hp;
}			t_player;

#endif