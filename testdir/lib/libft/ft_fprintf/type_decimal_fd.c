/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_decimal_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:24:44 by gpasztor          #+#    #+#             */
/*   Updated: 2023/04/29 16:46:05 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_fputdec(long int num, int fd, int *count)
{
	if (num < 0)
	{
		ft_fputchar('-', fd, count);
		if (*count == -1)
			return ;
		ft_fputdec(num * -1, fd, count);
		return ;
	}
	if (num > 9)
	{
		ft_fputdec(num / 10, fd, count);
		if (*count == -1)
			return ;
	}
	ft_fputchar(((num % 10) + '0'), fd, count);
}

void	ft_fputunsdec(unsigned int num, int fd, int *count)
{
	if (num > 9)
	{
		ft_fputdec(num / 10, fd, count);
		if (*count == -1)
			return ;
	}
	ft_fputchar(((num % 10) + '0'), fd, count);
}
