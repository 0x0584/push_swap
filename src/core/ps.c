/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:22:14 by archid-           #+#    #+#             */
/*   Updated: 2019/12/05 18:12:54 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"
#include "op.h"

t_ps		ps_alloc(char symb, size_t size)
{
	t_ps ps;

	if (!(ps = ALLOC(t_ps, 1, sizeof(struct s_ps_ds))))
		return (NULL);
	ps->symb = symb;
	ps->size = size;
	ps->stack = queue_init();
	return (ps);
}

void		ps_del(t_ps *aps)
{
	if (!SAFE_PTRVAL(aps))
		return ;
	queue_del(&(*aps)->stack, lstdel_helper);
	free(*aps);
	*aps = NULL;
}

bool		ps_issorted(t_ps ps_a, t_ps ps_b)
{
	t_qnode *walk;

	if (!ps_a || (ps_b && queue_size(ps_b->stack)))
		return (false);
	walk = ps_a->stack->head->next;
	while (walk->next != ps_a->stack->tail)
	{
		if (AS_NODE(walk->blob)->value > AS_NODE(walk->next->blob)->value)
			return (false);
		walk = walk->next;
	}
	return (true);
}

void		ps_sort_few(t_ps a, t_ps b, t_lst *ops)
{
	t_ps_array arr;

	arr = ps_vals_asarray(a);
	if (arr.size == 2 && arr.base[0] > arr.base[1])
		op_save(OP_INIT(OP_SWAP, APPLY_ON_A), ops, a, b);
	else if (arr.base[0] > arr.base[1] && arr.base[1] < arr.base[2])
		op_save(OP_INIT(arr.base[0] > arr.base[2] ? OP_ROT : OP_SWAP,
								APPLY_ON_A), ops, a, b);
	else if (arr.base[0] > arr.base[1] && arr.base[1] > arr.base[2])
	{
		op_save(OP_INIT(OP_SWAP, APPLY_ON_A), ops, a, b);
		op_save(OP_INIT(OP_RROT, APPLY_ON_A), ops, a, b);
	}
	else if (arr.base[0] < arr.base[2] && arr.base[2] < arr.base[1])
	{
		op_save(OP_INIT(OP_SWAP, APPLY_ON_A), ops, a, b);
		op_save(OP_INIT(OP_ROT, APPLY_ON_A), ops, a, b);
	}
	else if (arr.base[0] > arr.base[2] && arr.base[0] < arr.base[1])
		op_save(OP_INIT(OP_RROT, APPLY_ON_A), ops, a, b);
	free(arr.base);
}

t_ps_array	ps_vals_asarray(t_ps ps)
{
	t_ps_array	arr;
	size_t		i;
	t_qnode		*walk;

	if (!ps || !(arr.base = ALLOC(int *, queue_size(ps->stack) + 1,
									sizeof(int))))
		return ((t_ps_array){NULL, 0});
	i = 0;
	walk = ps->stack->head->next;
	while (walk != ps->stack->tail)
	{
		arr.base[i++] = AS_NODE(walk->blob)->value;
		walk = walk->next;
	}
	arr.size = i;
	return (arr);
}
