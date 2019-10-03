/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 04:53:40 by archid-           #+#    #+#             */
/*   Updated: 2019/10/03 19:23:31 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_ps		ps_alloc(size_t size)
{
	t_ps foo;

	size += 1;
	if (!(foo = ALLOC(t_ps, 1, sizeof(struct s_push_swap_stack))))
		return (NULL);
	if (!(foo->stack = ALLOC(t_val *, size, sizeof(t_val))))
	{
		free(foo);
		return (NULL);
	}
	foo->tail = foo->stack + size;
	foo->mark = foo->stack + size;
	return (foo);
}

void		ps_del(t_ps *aps)
{
	if (!SAFE_PTRVAL(aps))
		return ;
	free((*aps)->stack);
	free((*aps));
	*aps = NULL;
}

void		ps_push(t_ps ps, t_val e)
{
	if (ps && ps->mark > ps->stack)
	{
		*(ps->mark--) = e;
		return ;
	}
	ft_putendl_fd("warning: push failed. stack was full!", 2);
}

t_val		ps_pop(t_ps ps)
{
	if (ps && ps->mark <= ps->tail)
		return *(ps->mark++);
	ft_putendl_fd("warning: pop failed. stack was empty!", 2);
	return (ERROR_POP);
}

bool		ps_isempty(t_ps ps);
