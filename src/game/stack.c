/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 04:53:40 by archid-           #+#    #+#             */
/*   Updated: 2019/10/04 02:55:43 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_ps		ps_alloc(char label, size_t size)
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
	foo->orig = foo->stack + size;
	foo->label = label;
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
	if (!ps || ps->mark <= ps->stack || ps->mark > ps->tail)
	{
		ft_putendl_fd("warning: push failed. stack was full!", 2);
		return ;
	}
	*(ps->mark--) = e;
	ps->orig--;
}

t_val		ps_pop(t_ps ps)
{
	t_val foo;

	if (!ps || ps->mark > ps->tail)
	{
		ft_putendl_fd("warning: pop failed. stack was empty!", 2);
		return (ERROR_POP);
	}
	foo = *(++ps->mark);
	ps->orig++;
	return (foo);
}

bool		ps_isempty(t_ps ps)
{
	return (ps->mark == ps->tail);
}

void		ps_dump(t_ps ps)
{
	size_t i;
	size_t length;

	if (!ps || ps->mark > ps->tail || ps->mark <= ps->stack)
	{
		ft_putendl_fd(ps ? "warning: dump failed. `mark' is out of bound!"
							: "fatal: arg(s) expected was NULL!", 2);
		return ;
	}
	if (ps_isempty(ps))
	{
		ft_putendl_fd("note: cannot dump empty stack.", 2);
		return ;
	}

	ft_putchar(ps->label);
	ft_putstr(": [size = ");
	ft_putnumber((ps->tail - ps->stack) + 1);
	ft_putstr("] [length = ");
	ft_putnumber(length = (ps->tail - ps->mark));
	ft_putendl("]");

	i = 0;
	while (i++ < length)
	{
		ft_putnumber(ps->mark[i]);
		ft_putendl("");
	}
	ft_putendl("");
}
