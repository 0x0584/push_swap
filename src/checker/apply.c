/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 04:55:25 by archid-           #+#    #+#             */
/*   Updated: 2019/10/19 15:57:42 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

bool	op_push(t_lst *foo, t_lst *bar, t_op op)
{
	ft_putendl("this");
	if ((op.which != OP_TO_A && op.which != OP_TO_B)
			|| (OP_TO_A && !bar) || (OP_TO_B && !foo))
		return (false);

	if (op.which == OP_TO_A)
		do_psh(foo, bar);
	else
	{
		ft_putendl("wait");
		do_psh(bar, foo);
	}
	return (true);
}

bool	op_swap(t_lst *foo, t_lst *bar, t_op op)
{
	if (!foo || !bar)
		return (false);
	if (op.which == OP_TO_A || op.which == OP_TO_BOTH)
		do_swp(foo);
	if (op.which == OP_TO_A || op.which == OP_TO_BOTH)
		do_swp(bar);
	return (true);
}

bool	op_rotation(t_lst *foo, t_lst *bar, t_op op)
{
	if (!bar || !foo)
		return (false);
	if (op.which == OP_TO_A || op.which == OP_TO_BOTH)
		do_rot(foo, true);
	if (op.which == OP_TO_A || op.which == OP_TO_BOTH)
		do_rot(bar, true);
	return (true);

}

bool	op_rev_rotation(t_lst *foo, t_lst *bar, t_op op)
{
	if (!bar || !foo)
		return (false);
	if (op.which == OP_TO_A || op.which == OP_TO_BOTH)
		do_rot(foo, false);
	if (op.which == OP_TO_A || op.which == OP_TO_BOTH)
		do_rot(bar, false);
	return (true);
}

t_op		op_which(const char *str_op)
{
	t_op op;

	if (!str_op || !*str_op)
		op.which = OP_NIL;
	op.which = false;
	op.op = OP_NIL;
	if (*str_op == 'p')
		op.op = OP_PUSH;
	else if (*str_op == 's')
		op.op = OP_SWAP;
	else if (*str_op == 'r')
		op.op = (str_op[1] && str_op[1] == 'r' ? OP_RREV : OP_REV);
	if ((*str_op == 's' && str_op[1] == 's')
			|| (*str_op == 'r' && str_op[1] == 'r' )
			|| (*str_op == 'r' && str_op[1] == 'r' && str_op[2] == 'r'))
		op.which = OP_TO_BOTH;
	else
		op.which = WHICH_HELPER(str_op[1 + (str_op[1] == 'r')]);
	return (op);
}
