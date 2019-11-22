/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:41:51 by archid-           #+#    #+#             */
/*   Updated: 2019/11/23 00:16:02 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void		op_dump(t_op op)
{
	char *prefix;
	char *suffix;

	prefix = "psrr";
	suffix = "ab";
	ft_printf("%c", prefix[op.op]);
	if (op.op == OP_RROT)
		ft_printf("%c", 'r');
	if (op.which != APPLY_ON_BOTH)
		ft_printf("%c", suffix[op.which]);
	else if (op.op == OP_ROT || op.op == OP_RROT)
		ft_printf("%c", 'r');
	else
		ft_printf("%c", 's');
	ft_printf("\n");
}

bool		op_isvalid(char const *str, t_op *op)
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

bool		op_apply(t_op op, t_ps foo, t_ps bar)
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

# define AS_NODE(foo) ((t_ps_node *)foo)

bool		op_dopsh(t_ps dest, t_ps src)
{
	if (!dest || !src || !src->len || dest->len == dest->size + 1)
	{

		ft_printf("exit from false! dest: %d / %d | src: %d / %d\n",
				  dest->len, dest->size, src->len, src->size);
		return (false);
	}
	ft_dprintf(2, ">> APPLYING OP: %{red_fg}p%c%{reset}\n", dest->symb);
	ft_lstadd(&dest->stack, ft_lstpeek(&src->stack));

	if (AS_NODE(dest->stack->content)->value < dest->min.value)
		dest->min.value = AS_NODE(dest->stack->content)->value;
	if (AS_NODE(dest->stack->content)->value > dest->max.value)
		dest->max.value = AS_NODE(dest->stack->content)->value;
	src->len--;
	dest->len++;
	return (true);
}

bool		op_doswp(t_ps ps)
{
	t_lst foo;
	t_lst bar;

	if (!ps || ps->len < 2)
		return (false);
	ft_dprintf(2, ">> APPLYING OP: %{red_fg}s%c%{reset}\n", ps->symb);
	foo = ft_lstpeek(&ps->stack);
	bar = ft_lstpeek(&ps->stack);
	ft_lstadd(&ps->stack, foo);
	ft_lstadd(&ps->stack, bar);
	return (true);
}

/*
   FIXME: tracking the tail of the stack is optimal for rotation!
   so for the moment, i'll be using a singly linked list but when
   finilizing the work, i'll switch to a doubly linked list.

   also, rotation might recieve an argument indicating the number
   of rotations, so that we can do it at once. this could be achieved
   by creating a new list containing the elements that we can to rotate,
   and put them on head or tail based on rotation.
*/

bool		op_dorot(t_ps ps, bool is_up)
{
	t_lst node;

	if (!ps || ps->len < 2)
		return (false);
	ft_dprintf(2, ">> APPLYING OP: %{red_fg}r%s%c%{reset}\n",
			   !is_up ? "r" : "", ps->symb);

	/* ft_lstiter(ps->stack, helper_node_dump); */
	/* getchar(); */

	if (is_up)
		node = ft_lstpeek(&ps->stack);
	else
		node = ft_lstpop(&ps->stack);

	if (is_up)
		ft_lstpush(&ps->stack, node);
	else
		ft_lstadd(&ps->stack, node);

	/* ft_lstiter(ps->stack, helper_node_dump); */
	/* getchar(); */

	return (true);
}
