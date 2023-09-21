/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:38:40 by ffederol          #+#    #+#             */
/*   Updated: 2023/09/21 20:29:27 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include <math.h>

int			manage_graphics(void *param);
void		draw_line(void *param);
void		ft_minimap(void *param);
uint32_t	convert_to_rgba(uint8_t *pixels);
void		port_counter(void *param);

#endif