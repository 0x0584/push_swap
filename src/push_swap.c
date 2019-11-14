/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:18:20 by archid-           #+#    #+#             */
/*   Updated: 2019/11/14 12:10:05 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "reader.h"
#include "ft_printf.h"

void helper_op_dump(t_lst e)
{
	t_op *op;

	op = e->content;
	op_dump(*op);
}

void helper_op_free(void *content, size_t size)
{
	if (size)
		free(content);
}

void	ps_setorder(t_ps a)
{
	t_ps sorted_a;
	t_dlst walk, s_walk;
	int index;

	index = 0;
	sorted_a = ps_mergesort(a);
	ft_dprintf(2, "%{blue_fg}Initial state%{reset}\n");
	dump_stacks(a, sorted_a);
	s_walk = sorted_a->head;
	while (s_walk)
	{
		walk = a->head;
		while (walk)
			if (GET_PS_NODE(walk)->val == GET_PS_NODE(s_walk)->val)
				break ;
			else
				walk = walk->next;
		GET_PS_NODE(walk)->ord = index++;
		s_walk = s_walk->next;
	}
	ps_del(&sorted_a);
}

void	do_ops_intract(t_ps a, t_ps b)
{
	char *s_op = NULL;
	t_op op;

	while (gnl(0, &s_op))
	{
		if (!op_isvalid(s_op, &op))
			break;
		op_apply(op, a, b);
		dump_stacks(a, b);
		free(s_op);
	}

}

void	push_swap(t_ps a, t_ps b)
{
	t_lst ops;

	if (ps_issorted(a, b))
		return ;

	ops = NULL;
	ps_setorder(a);
	do_ops_intract(a, b);
	/* ps_split_ranges(a, b, &ops); */
	/* ps_refill(a, b, &ops); */
	ft_lstiter(ops, helper_op_dump);
	ft_lstdel(&ops, helper_op_free);

	/* fill_stack_b(a, b, find_mids(sorted_a, mids)); */
}

int		main(int argc, char **argv)
{
	t_ps ps_a;
	t_ps ps_b;

	if (!(ps_a = read_args(argc, argv)))
		return (EXIT_FAILURE);

	push_swap(ps_a, ps_b = ps_alloc('B', ps_a->size));
	ps_del(&ps_a);
	ps_del(&ps_b);

	return (0);
}
