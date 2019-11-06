/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:41:51 by archid-           #+#    #+#             */
/*   Updated: 2019/11/06 01:25:57 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "ft_printf.h"

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

/* FIXME: use array instead of sending two pointers */
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

bool		op_dopsh(t_ps dest, t_ps src)
{
	if (!dest || !src || !src->len || dest->len == dest->size)
		return (false);
	ft_dprintf(2, ">> APPLYING OP: %{red_fg}p%c%{reset}\n", dest->symb);
	ft_dlstadd(&dest->head, ft_dlstpeek(&src->head));
	src->len--;
	dest->len++;
	return (true);
}

bool		op_doswp(t_ps ps)
{
	t_dlst foo;
	t_dlst bar;

	if (!ps || ps->len < 2)
		return (false);
	ft_dprintf(2, ">> APPLYING OP: %{red_fg}s%c%{reset}\n", ps->symb);
	foo = ft_dlstpeek(&ps->head);
	bar = ft_dlstpeek(&ps->head);
	ft_dlstadd(&ps->head, foo);
	ft_dlstadd(&ps->head, bar);
	return (true);
}

bool		op_dorot(t_ps ps, bool is_up)
{
	t_dlst node;
	t_dlst walk;
	t_dlst tmp;

	if (!ps || ps->len < 2)
		return (false);
	/* else if (ps->len == 2) */
	/* 	return (op_doswp(ps)); */
	ft_dprintf(2, ">> APPLYING OP: %{red_fg}r%s%c%{reset}\n",
			   !is_up ? "r" : "", ps->symb);
	if (is_up)
		node = ft_dlstpeek(&ps->head);
	else
		node = ft_dlstpop(&ps->head);
	if (is_up)
		ft_dlstpush(&ps->head, node);
	else
		ft_dlstadd(&ps->head, node);
	/* walk = ps->head; */
	/* while (walk) */
	/* { */
	/* 	helper_node_dump(walk); */
	/* 	walk = walk->next; */
	/* } */
	/* ft_putendl("after head"); */
	/* getchar(); */
	/* walk = ps->tail; */
	/* while (walk) */
	/* { */
	/* 	helper_node_dump(walk); */
	/* 	walk = walk->prev; */
	/* } */
	/* ft_putendl("after tail"); */
	/* getchar(); */
	/* ft_dlstadd(is_up ? &ps->tail : &ps->head, node); */
	return (true);
}
