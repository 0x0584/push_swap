/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 04:55:25 by archid-           #+#    #+#             */
/*   Updated: 2019/10/13 19:03:38 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

bool	apply_push(t_ps foo, t_ps bar, int which)
{
	if (!foo || !bar || (which != OP_TO_A && which != OP_TO_B))
		return (false);
	ps_psh(which == OP_TO_A ? foo : bar, which == OP_TO_A ? bar : foo);
	return (true);
}

bool	apply_swap(t_ps foo, t_ps bar, int which)
{
	if (!foo || !bar)
		return (false);
	if (which == OP_TO_A || which == OP_TO_BOTH)
		ps_swp(foo);
	if (which == OP_TO_A || which == OP_TO_BOTH)
		ps_swp(bar);
	return (true);
}

bool	apply_rotation(t_ps foo, t_ps bar, int which)
{
	if (!bar || !foo)
		return (false);
	if (which == OP_TO_A || which == OP_TO_BOTH)
		ps_rot(foo, true);
	if (which == OP_TO_A || which == OP_TO_BOTH)
		ps_rot(bar, true);
	return (true);

}

bool	apply_rev_rotation(t_ps foo, t_ps bar, int which)
{
	if (!bar || !foo)
		return (false);
	if (which == OP_TO_A || which == OP_TO_BOTH)
		ps_rot(foo, false);
	if (which == OP_TO_A || which == OP_TO_BOTH)
		ps_rot(bar, false);
	return (true);
}

int		apply_which(const char *op, int *which)
{
	int operation;

	if (!op || !*op)
		return (OP_NIL);
	*which = false;
	operation = OP_NIL;
	if (*op == 'p')
		operation = OP_PUSH;
	else if (*op == 's')
		operation = OP_SWAP;
	else if (*op == 'r')
		operation = (op[1] && op[1] == 'r' ? OP_RREV : OP_REV);
	if ((*op == 's' && op[1] == 's') || (*op == 'r' && op[1] == 'r' )
			|| (*op == 'r' && op[1] == 'r' && op[2] == 'r'))
		*which = OP_TO_BOTH;
	else
		*which = WHICH_HELPER(op[1 + (op[1] == 'r')]); /* BUG: WTF!! */
	return (operation);
}
