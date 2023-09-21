/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 08:07:55 by gpasztor          #+#    #+#             */
/*   Updated: 2023/04/29 16:45:40 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_fprintf(int fd, const char *input, ...);
//character type
int		ft_fputchar(char ch, int fd, int *count);
int		ft_fputstr(char *str, int fd, int *count);
//decimal type
void	ft_fputdec(long int num, int fd, int *count);
void	ft_fputunsdec(unsigned int num, int fd, int *count);
//hexadecimal type
void	ft_fputlhex(unsigned int num, int fd, int *count);
void	ft_fputuhex(unsigned int num, int fd, int *count);
int		ft_fputptr(unsigned long long ptr, int ptrcount, int fd, int *count);

#endif
