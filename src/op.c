/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:41:51 by archid-           #+#    #+#             */
/*   Updated: 2019/10/22 03:43:32 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

bool	op_which(t_ps foo, t_ps bar, int which);

bool	op_dopsh(t_ps dest, t_ps src)
{
	if (!dest || !src || src->nodes)
		return (false);
	return (true);
}

bool	op_doswp(t_ps stack);
bool	op_dorot(t_ps stack);
bool	op_dorrot(t_ps stack);
