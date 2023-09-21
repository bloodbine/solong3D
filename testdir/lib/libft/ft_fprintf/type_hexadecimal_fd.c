/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_hexadecimal_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:26:50 by gpasztor          #+#    #+#             */
/*   Updated: 2023/04/29 16:46:28 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_fputlhex(unsigned int num, int fd, int *count)
{
	if (num > 16)
	{
		ft_fputlhex(num / 16, fd, count);
		if (*count == -1)
			return ;
	}
	if (num == 16)
		ft_fputstr("10", fd, count);
	else if (num % 16 < 10)
		ft_fputchar(((num % 16) + '0'), fd, count);
	else
		ft_fputchar(((num % 16) - 10 + 'a'), fd, count);
}

void	ft_fputuhex(unsigned int num, int fd, int *count)
{
	if (num > 16)
	{
		ft_fputuhex(num / 16, fd, count);
		if (*count == -1)
			return ;
	}
	if (num == 16)
		ft_fputstr("10", fd, count);
	else if (num % 16 < 10)
		ft_fputchar((num % 16) + '0', fd, count);
	else
		count += ft_fputchar(((num % 16) - 10 + 'A'), fd, count);
}

int	ft_fputptr(unsigned long long ptr, int ptrcount, int fd, int *count)
{
	if (ptr > 16)
		ptrcount += ft_fputptr(ptr / 16, ptrcount, fd, count);
	if ((ptr / 16 == 0 || ptr % 16 == 0) && ptrcount == 0)
		ptrcount += ft_fputstr("0x", fd, count);
	if (*count == -1)
		return (-1);
	if (ptr == 16)
		ptrcount += ft_fputstr("10", fd, count);
	else if (ptr % 16 < 10)
		ptrcount += ft_fputchar(((ptr % 16) + '0'), fd, count);
	else
		ptrcount += ft_fputchar(((ptr % 16) - 10 + 'a'), fd, count);
	if (*count == -1)
		return (-1);
	return (ptrcount);
}
