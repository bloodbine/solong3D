/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:53:44 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/18 17:40:41 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size && count > 18446744073709551615UL / size)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == 0)
		return (NULL);
	ft_bzero(ptr, size * count);
	return (ptr);
}
