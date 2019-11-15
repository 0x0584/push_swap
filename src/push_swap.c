/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:18:20 by archid-           #+#    #+#             */
/*   Updated: 2019/11/16 00:54:56 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "reader.h"
#include "ft_printf.h"

void	op_save(t_op op, t_lst *ops, t_ps a, t_ps b)
{
	if (!op_apply(op, a, b))
		ft_dprintf(2, "%{yellow_fg}note: cannot apply operation!\n%{reset}");
	ft_lstpush(ops, ft_lstnew(&op, sizeof(t_op)));
}


int		find_fit(t_ps_node *node, t_ps b)
{
	t_lst walk;

	walk = b->stack;
	while (walk)
	{
		if (node == walk->content)
		{

		}
		walk = walk->next;
	}
	return (0);
}

t_lst	find_ops(t_ps_node *node, int index, t_ps b)
{
	t_lst	ops;
	int		n_rots;

	ops = NULL;
	n_rots = find_fit(node, b);




	return (ops);
}

void	push_swap(t_ps a, t_ps b)
{
	t_lst ops;
	t_lst walk;
	t_lst tmp_ops;
	t_lst optimal_ops;
	int index;

	if (ps_issorted(a, b))
		return ;

	ops = NULL;
	index = 0;
	optimal_ops = NULL;
	op_save(OP_INIT(OP_PUSH, APPLY_ON_B), &ops, a, b);
	while (a->len)
	{
		walk = a->stack;
		while (walk)
		{
			tmp_ops = find_ops(walk->content, index++, b);
			if (ft_lstlen(tmp_ops) < ft_lstlen(optimal_ops))
			{
				ft_lstdel(&optimal_ops, lstdel_helper);
				optimal_ops = tmp_ops;
			}
			walk = walk->next;
		}
	}
	while (b->len)
		op_save(OP_INIT(OP_PUSH, APPLY_ON_A), &ops, a, b);
	ft_lstiter(ops, helper_op_dump);
	ft_lstdel(&ops, helper_op_free);

	ft_printf("FINAL RESULT: %s", ps_issorted(a, b) ? "OK" : "KO");
}

int		main(int argc, char **argv)
{
	t_ps ps_a;
	t_ps ps_b;

	if (!(ps_a = read_args(argc, argv)))
		return (EXIT_FAILURE);
	push_swap(ps_a, ps_b = ps_alloc('b', ps_a->size));
	ps_del(&ps_a);
	ps_del(&ps_b);
	return (0);
}
