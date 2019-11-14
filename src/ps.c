/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:22:14 by archid-           #+#    #+#             */
/*   Updated: 2019/11/14 15:49:44 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"
#include "op.h"
#include "ft_printf.h"

void	ps_dump(t_ps ps)
{
	t_dlst		walk;
	t_ps_node	*node;

	if (!ps)
		return ;
	ft_dprintf(2, "stack: %c[%zu/%zu]\n------------------\n",
			ps->symb, ps->len, ps->size);
	walk = ps->head;
	while (walk)
	{
		node = (t_ps_node *)walk->blob;
		ft_dprintf(2, "{%p/%d: %d}\n", walk, node->ord, node->val);
		walk = walk->next;
	}
	ft_dprintf(2, "------------------\n");
}

t_ps	ps_alloc(char symb, size_t size)
{
	t_ps ps;

	if (!(ps = ALLOC(t_ps, 1, sizeof(struct s_ps_ds))))
		return (NULL);
	ps->symb = symb;
	ps->size = size;
	return (ps);
}

void	ps_del(t_ps *aps)
{
	if (!SAFE_PTRVAL(aps))
		return ;
	ft_dlstdel(lstdel_helper, &(*aps)->head);
	free(*aps);
	*aps = NULL;
}

bool	ps_issorted(t_ps ps_a, t_ps ps_b)
{
	t_dlst walk;

	if (!ps_a || !ps_a->head || (ps_b && ps_b->head))
		return (false);
	/* ps_dump(ps); */
	walk = ps_a->head;
	while (walk->next)
	{
		if (((t_ps_node *)walk->blob)->val
				> ((t_ps_node *)walk->next->blob)->val)
			return (false);
		walk = walk->next;
	}
	return (true);
}

t_ps	ps_clone(t_ps const ps)
{
	t_ps	duped;
	t_dlst	node;
	t_dlst	walk;

	duped = ps_alloc('Y', ps->size); /* deal with it my man! */
	duped->size = ps->size;
	duped->len = ps->len;
	walk = ps->head;
	while (walk)
	{
		node = ft_dlstpush(&duped->head, ft_dlstnew(walk->blob, walk->size));
		if (!walk->next)
			duped->tail = node;
		walk = walk->next;
	}
	return (duped);
}

int		ps_node_cmp(t_dlst foo, t_dlst bar)
{
	if (!foo || !bar)
		return (-1);
	return (GET_PS_NODE(bar)->val - GET_PS_NODE(foo)->val);
}

t_ps	ps_mergesort(t_ps ps)
{
	t_ps sorted;

	sorted = ps_clone(ps);
	ft_dlstmergesort(&sorted->head, ps_node_cmp);
	sorted->tail = ft_dlst_gettail(sorted->head);
	return (sorted);
}

t_range		ps_whichrange(t_val val, t_ps_node *mid)
{
	/* TODO: check whether mid is included or excluded */
	if (val < mid->val)
		return (RANGE_LOW);
	return (RANGE_HIGH);
}

/* FIXME: find a general way to cut ranges */
t_range		ps_find_ranges(t_ps a)
{
	if (a->size <= 7)
		return (RANGE_NA);
	else if (a->size <= 100)
		return (RANGE_LOW);
	return (RANGE_HIGH);
}
