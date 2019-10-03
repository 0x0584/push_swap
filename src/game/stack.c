/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 04:53:40 by archid-           #+#    #+#             */
/*   Updated: 2019/10/03 05:37:29 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_stack.h"

t_ps		ps_alloc(size_t size)
{
	t_ps foo;

	if (!(foo = ALLOC(t_ps, 1, sizeof(struct s_push_swap_stack))))
		return (NULL);
	if (!(foo->stack = ALLOC(t_s64 *, size, sizeof(t_s64))))
	{
		free(foo);
		return (NULL);
	}
	foo->size = size;
	foo->head = foo->stack;
	return foo;
}

void		ps_del(t_ps *aps)
{

}
