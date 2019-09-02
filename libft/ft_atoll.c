/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 04:39:36 by archid-           #+#    #+#             */
/*   Updated: 2019/07/22 04:40:36 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_int128	ft_atoll(const char *s)
{
	t_int128	result;
	t_int128	sign;
	char		*str;
	size_t		len;

	sign = 1;
	str = (char *)s;
	while (ft_isspace(*str))
		str++;
	if ((*str == '-' || *str == '+') && (*str++ == '-'))
		sign = -1;
	len = 0;
	while (ft_isdigit(str[len]))
		len++;
	result = 0;
	while (ft_isdigit(*str))
		result += ft_power(10, --len) * (*str++ - '0');
	return ((t_int128)result * sign);
}
