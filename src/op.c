/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:41:51 by archid-           #+#    #+#             */
/*   Updated: 2019/10/24 05:46:22 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void			op_dump(t_op op)
{
	char *prefix;
	char *suffix;

	prefix = "psrr";
	suffix = "ab";
	printf("op is: %c", prefix[op.op]);
	if (op.op == OP_RROT)
		printf("%c", 'r');
	if (op.which != APPLY_ON_BOTH)
		printf("%c", suffix[op.which]);
	else if (op.op == OP_ROT || op.op == OP_RROT)
		printf("%c", 'r');
	else
		printf("%c", 's');
	printf("\n");
}

bool			op_isvalid(char const *str, t_op *op)
{
	char bar[4];

	if (!str ||  !*str || !op || ft_strlen(ft_strncpy(bar, str, 3)) < 2)
		return (false);
	if (bar[0] == 'p' && (bar[1] == 'a' || bar[1] == 'b') && !bar[2])
			*op = OP_INIT(OP_PUSH, bar[1] == 'b');
	else if (bar[0] == 's' && !bar[2])
	{
		if (bar[1] == 'a' || bar[1] == 'b')
			*op = OP_INIT(OP_SWAP, bar[1] == 'b');
		else if (bar[1] == 's')
			*op = OP_INIT(OP_SWAP, APPLY_ON_BOTH);
	}
	else if (bar[0] == 'r')
	{
		op->which = APPLY_ON_BOTH;
		if (bar[1] == 'r' && (bar[2] == 'a' || bar[2] == 'b'))
			*op = OP_INIT(OP_RROT, bar[2] == 'b');
		else if (bar[1] == 'a' || bar[1] == 'b')
			*op = OP_INIT(OP_ROT, bar[1] == 'b');
		else if (bar[1] == 'r' && bar[2] == 'r')
			op->op = OP_RROT;
		else if (bar[1] == 'r' && !bar[2])
			op->op = OP_ROT;
	}
	return (OP_IS_GOOD(op));
}

bool			op_apply(t_op op, t_ps foo, t_ps bar)
{
	if (op.op == OP_PUSH)
		return (op_dopsh(!op.which ? foo : bar, !op.which ? bar : foo));
	if (op.op == OP_SWAP)
	{
		if (op.which != APPLY_ON_BOTH)
			return (op_doswp(!op.which ? foo : bar));
		return (op_doswp(foo) && op_doswp(bar));
	}
	if (op.op == OP_ROT || op.op == OP_RROT)
	{
		if (op.which != APPLY_ON_BOTH)
			return (op_dorot(!op.which ? foo : bar, op.op == OP_ROT));
		return (op_dorot(foo, op.op == OP_ROT)
					&& op_dorot(bar, op.op == OP_ROT));
	}
	return (false);
}

bool			op_dopsh(t_ps dest, t_ps src)
{
	t_dlst node;

	if (!dest || !src || !src->len || dest->len == dest->size)
		return (false);
	node = ft_dlstpop(&src->tail->prev);
	ft_dlstpush(&dest->tail->prev, node);
	src->len--;
	dest->len++;
	return (true);
}

bool			op_doswp(t_ps stack)
{
	t_dlst foo;
	t_dlst bar;

	if (!stack || stack->len < 2)
		return (false);
	foo = ft_dlstpop(&stack->tail->prev);
	bar = ft_dlstpop(&stack->tail->prev);
	ft_dlstpush(&stack->tail->prev, bar);
	ft_dlstpush(&stack->tail->prev, foo);
	return (true);
}

static void		dorot_helper(t_ps stack, t_dlst *anode,
								bool is_up, bool is_get)
{
	if (is_get)
	{
		if (is_up)
			*anode = ft_dlstpeek(&stack->head->next);
		else
			*anode = ft_dlstpop(&stack->tail->prev);
		return ;
	}
	if (is_up)
		ft_dlstpush(&stack->tail->prev, *anode);
	else
		ft_dlstadd(&stack->head->next, *anode);
}

bool			op_dorot(t_ps stack, bool is_up)
{
	t_dlst node;

	if (!stack || stack->len < 2)
		return (false);
	else if (stack->len == 2)
		return (op_doswp(stack));
	dorot_helper(stack, &node, is_up, true);
	dorot_helper(stack, &node, is_up, false);
	return (true);
}
