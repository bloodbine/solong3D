/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:38:40 by ffederol          #+#    #+#             */
/*   Updated: 2023/09/16 14:23:16 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "vector.h"
# include <fcntl.h>

// textures: N, E, S, W, D, NULL
// directions: (x|y)  N = (0|-1), E = (1|0), S = (0|1), W = (-1|0)
typedef struct s_parse
{
	char			*textures[6];
	char			**worldmap;
	int				error;
	uint32_t		floor;
	uint32_t		roof;
	t_int_vector	mapsizes;
	t_int_vector	playerpos;
	t_int_vector	playerdir;
	t_int_vector	ppos[2];
	int				pcount;
}				t_parse;

void		parse_free(t_parse *data);
void		run_dfs(t_parse *data);
uint32_t	sort_rgba(char	*line);
void		sort_map(t_parse *data, int fd);
void		sort_data(t_parse *data, int fd, int *found, char *buff);
void		find_player(t_parse *data);
void		file_check(t_parse *data);
int			character_check(t_parse *data, char **map, int i, int j);
void		padding(t_parse *data, size_t len, size_t col);
t_parse		*parse(int argc, char **argv);
void		parse_error(char *error_message);
uint32_t	rgbtohex(int r, int g, int b, int a);

#endif