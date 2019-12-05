/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 00:05:21 by archid-           #+#    #+#             */
/*   Updated: 2019/12/05 15:47:43 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

bool	op_dopsh(t_ps dest, t_ps src)
{
	if (!dest || !src || !src->len)
		return (false);
	queue_push_front(dest->stack, queue_deq(src->stack));
	src->len--;
	dest->len++;
	return (true);
}

bool	op_doswp(t_ps ps)
{
	t_qnode *foo;
	t_qnode *bar;

	if (!ps || ps->len < 2)
		return (false);
	foo = queue_deq(ps->stack);
	bar = queue_deq(ps->stack);
	queue_push_front(ps->stack, foo);
	queue_push_front(ps->stack, bar);
	return (true);
}

bool	op_dorot(t_ps ps, bool is_up)
{
	if (!ps || ps->len < 2)
		return (false);
	if (is_up)
		queue_enq(ps->stack, queue_deq(ps->stack));
	else
		queue_push_front(ps->stack, queue_pop(ps->stack));
	return (true);
}

void	helper_op_dump(t_qnode *e)
{
	t_op *op;

	op = e->blob;
	op_dump(*op);
}

void	append_ops(t_ps a, t_ps b, t_lst *ops, t_lst *new)
{
	t_lst walk;

	if (!SAFE_PTRVAL(new))
		return ;
	walk = *new;
	while (walk)
	{
		op_save(*(t_op *)walk->content, ops, a, b);
		walk = walk->next;
	}
	ft_lstdel(new, lstdel_helper);
}
