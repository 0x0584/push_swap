/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 23:06:41 by archid-           #+#    #+#             */
/*   Updated: 2019/10/16 04:02:18 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

static void		ps_asc_quicksort(t_ps stack)
{

}

/* NOTE: fuck off */
static void		set_mids(t_ps sorted, t_val *mid1, t_val *mid2)
{

}

t_ps			ps_dup(t_ps stack)
{
	return NULL;
}

enum e_valcmp
{
	CMP_EQ, CMP_MOD,
	CMP_LT, CMP_GT,
	CMP_LE, CMP_GE
};

bool val_cmp(t_val val, t_val a, enum e_valcmp cmp)
{
	if (cmp == CMP_EQ)
		return (val == a);
	else if (cmp == CMP_LT)
		return (val < a);
	else if (cmp == CMP_GT)
}

/* NOTE: those mids 1 and 2 are just the index of elements n/3 and (2*n)/3 */
void			split_by_mids(t_ps stack, t_ps b)
{
	t_ps	sorted;
	t_val	u;
	t_val	v;

	sorted = (t_ps)ps_dup(stack);	/* FIXME: pointers are dangerous */
	ps_asc_quicksort(stack);
	set_mids(sorted, &u, &v);
	while (stack->mark++ < stack->tail)
	{
		if (VAL_EQUAL(u, *stack->mark))
		{

		}
	}

}
