/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnumber_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 03:30:09 by archid-           #+#    #+#             */
/*   Updated: 2019/07/18 22:23:48 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnumber_fd(int n, int fd)
{
	t_uint64 u;

	u = (n < 0) ? -n : n;
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (u > 9)
		ft_putnumber_fd(u / 10, fd);
	ft_putchar_fd(u % 10 + '0', fd);
}
