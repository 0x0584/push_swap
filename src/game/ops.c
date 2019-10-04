/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 16:56:31 by archid-           #+#    #+#             */
/*   Updated: 2019/10/04 02:50:11 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	ps_psh(t_ps dest, t_ps src)
{
	ps_push(dest, ps_pop(src));
}

void	ps_swp(t_ps stack)
{
	t_val foo;
	t_val bar;

	foo = ps_pop(stack);
	bar = ps_pop(stack);
	ps_push(stack, foo);
	ps_push(stack, bar);
}

void	ps_rot(t_ps stack, bool isrev)
{
	(void)stack;
	(void)isrev;
}
