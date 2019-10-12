/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 04:53:40 by archid-           #+#    #+#             */
/*   Updated: 2019/10/12 15:18:57 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_ps		ps_alloc(char label, size_t size)
{
	t_ps foo;

	foo = NULL;
	if (!(foo = ALLOC(t_ps, 1, sizeof(struct s_push_swap_stack)))
			|| !(foo->head = ALLOC(t_val *, size--, sizeof(t_val))))
	{
		free(foo);
		return (NULL);
	}
	foo->tail = foo->head + size;
	foo->mark = foo->tail;
	foo->label = label;
	return (foo);
}

void		ps_del(t_ps *aps)
{
	if (!SAFE_PTRVAL(aps))
		return ;
	free((*aps)->head);
	free((*aps));
	*aps = NULL;
}

void		ps_push(t_ps ps, t_val e)
{
	if (!ps || PS_ISFULL(ps))
	{
		ft_putendl_fd("warning: push failed. stack was full!", 2);
		return ;
	}
	ft_putstr_fd("pushed(", 2);
	ft_putnumber_fd(e, 2);
	ft_putendl_fd(")", 2);
	*ps->mark-- = e;
}

t_val		ps_pop(t_ps ps)
{
	/* t_val pop; */

	if (!ps || PS_ISEMPTY(ps))
	{
		ft_putendl_fd("warning: pop failed. stack was empty!", 2);
		return (ERROR_POP);
	}
	ft_putstr_fd("poped(", 2);
	ft_putnumber_fd(*(ps->mark + 1), 2);
	ft_putendl_fd(")", 2);
	return (*(++ps->mark));
}

bool		ps_issorted(t_ps ps)
{
	t_val		*walk;

	if (!ps)
		return (false);
	walk = ps->mark;
	while (++walk != ps->tail)
		if (*walk < *(walk + 1))
			return (false);
	return (true);
}

void		ps_dump(t_ps ps)
{
	size_t i;
	size_t length;

	if (!ps || ps->mark > ps->tail || ps->mark <= ps->head)
	{
		ft_putendl_fd(ps ? "warning: dump failed. `mark' is out of bound!"
							: "fatal: arg(s) expected was NULL!", 2);
		return ;
	}
	if (PS_ISEMPTY(ps))
	{
		ft_putendl_fd("note: cannot dump empty stack.", 2);
		return ;
	}

	ft_putchar(ps->label);
	ft_putstr(": [size = ");
	ft_putnumber(PS_SIZE(ps));
	ft_putstr("] [length = ");
	ft_putnumber(length = PS_LENGTH(ps));
	ft_putendl("]");

	i = 0;
	while (i++ < length)
	{
		ft_putnumber(ps->mark[i]);
		ft_putendl("");
	}
	ft_putendl("");
}
