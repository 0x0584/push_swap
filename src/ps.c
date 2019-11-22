/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:22:14 by archid-           #+#    #+#             */
/*   Updated: 2019/11/22 21:14:09 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"
#include "ps_node.h"
#include "op.h"

t_ps	ps_alloc(char symb, size_t size)
{
	t_ps ps;

	if (!(ps = ALLOC(t_ps, 1, sizeof(struct s_ps_ds))))
		return (NULL);
	ps->symb = symb;
	ps->size = size;
	ps->max = (t_ps_node){INT_MIN, 0, 0};
	ps->min = (t_ps_node){INT_MAX, 0, 0};
	return (ps);
}

void	ps_del(t_ps *aps)
{
	if (!SAFE_PTRVAL(aps))
		return ;
	ft_lstdel(&(*aps)->stack, lstdel_helper);
	free(*aps);
	*aps = NULL;
}

bool	ps_issorted(t_ps ps_a, t_ps ps_b)
{
	t_lst walk;

	if (!ps_a || !ps_a->stack || (ps_b && ps_b->stack))
		return (false);
	/* ps_dump(ps); */
	walk = ps_a->stack;
	while (walk->next)
	{
		if (((t_ps_node *)walk->content)->value
				> ((t_ps_node *)walk->next->content)->value)
			return (false);
		walk = walk->next;
	}
	return (true);
}

bool	ps_node_cmp(t_ps_node *u, t_ps_node *v, t_cmp cmp_op)
{
	if (!u || !v)
		return (false);
	if (cmp_op == CMP_EQ)
		return (u->value == v->value);
	else if (cmp_op == CMP_NEQ)
		return (u->value != v->value);
	else if (cmp_op == CMP_LE)
		return (u->value <= v->value);
	else if (cmp_op == CMP_GE)
		return (u->value >= v->value);
	else if (cmp_op == CMP_LT)
		return (u->value < v->value);
	else if (cmp_op == CMP_GT)
		return (u->value > v->value);
	return (false);
}

bool		ps_check_node(t_ps ps, t_ps_node *node)
{
	t_lst walk;

	if (!ps || !node)
		return (false);
	walk = ps->stack;
	while (walk)
	{
		if (ps_node_cmp(walk->content, node, CMP_EQ))
			return (false);
		walk = walk->next;
	}
	return (true);
}
