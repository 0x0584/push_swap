/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:41:51 by archid-           #+#    #+#             */
/*   Updated: 2019/10/23 05:26:28 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

#define OP_PREFIX(c)		(c == 'p' || c == 's' || c == 'r')
#define OP_SUFFIX(c)		(c == 'a' || c == 'b' || c == 's' || c == 'r')
#define HAS_NL(s)			(*(s) == '\n' && !*((s) + 1))
#define OP_END(s)			(!*(s) || HAS_NL(s) || (*(s) == 'r' && !*((s) + 1)))

void			op_dump(t_op op)
{
	char *prefix = "psrr";
	char *suffix = "ab";


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

bool			op_isvalid(const char *str, t_op *op)
{
	size_t	len;

	if (!str)
		return (false);

	printf("(prefix: %d, suffix: %d, end: %d)\n",
		   OP_PREFIX(str[0]),
		   OP_SUFFIX(str[1]),
		   OP_END(str + 2));
	len = ft_strlen(str);
	if (len == 2)
	{
		if (str[0] == 'p' || str[0] == 's')
			op->op = (str[0] == 'p' ? OP_PUSH : OP_SWAP);
		else
			op->op = OP_ROT;
		if (str[1] == 's' || str[1] == 'r')
			op->which = APPLY_ON_BOTH;
		else
			op->which = (str[1] == 'a' ? APPLY_ON_A : APPLY_ON_B);
	}
	op->op = len == 3 ? OP_RROT : op->op;
	if (len == 3 && str[2] == 'r')
		op->which = APPLY_ON_BOTH;
	else if (len == 3)
		op->which = (str[2] == 'a' ? APPLY_ON_A : APPLY_ON_B);
	return (true);
}

bool			op_apply(t_op op, t_ps foo, t_ps bar)
{
	if (op.op == OP_PUSH)
		return op_dopsh(!op.which ? foo : bar, !op.which ? bar : foo);
	if (op.op == OP_SWAP)
	{
		if (op.which != APPLY_ON_BOTH)
			return op_doswp(!op.which ? foo : bar);
		return op_doswp(foo) && op_doswp(bar);
	}
	else if (op.op == OP_ROT || op.op == OP_RROT)
	{
		if (op.which != APPLY_ON_BOTH)
			return op_dorot(!op.which ? foo : bar, op.op == OP_ROT);
		return op_dorot(foo, op.op == OP_ROT)
			&& op_dorot(bar, op.op == OP_ROT);
	}
	return false;
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
		return op_doswp(stack);
	dorot_helper(stack, &node, is_up, true);
	dorot_helper(stack, &node, is_up, false);
	return (true);
}
