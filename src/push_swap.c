/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:18:20 by archid-           #+#    #+#             */
/*   Updated: 2019/12/05 18:15:07 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "reader.h"
#include "dump.h"

t_lst	compress_ops(t_lst ops)
{
	t_lst	walk;
	t_lst	tmp;
	t_op	*op[2];

	walk = ops;
	while (walk && walk->next)
	{
		op[0] = walk->content;
		op[1] = walk->next->content;
		if (((op[0]->op == OP_ROT && op[1]->op == OP_ROT)
				|| (op[0]->op == OP_RROT && op[1]->op == OP_RROT)
				|| (op[0]->op == OP_SWAP && op[1]->op == OP_SWAP))
			&& ((op[0]->which == APPLY_ON_A && op[1]->which == APPLY_ON_B)
				|| (op[1]->which == APPLY_ON_A && op[0]->which == APPLY_ON_B)))
		{
			tmp = walk->next;
			walk->next = walk->next->next;
			op[0]->which = APPLY_ON_BOTH;
			ft_lstdelone(&tmp, lstdel_helper);
		}
		walk = walk->next;
	}
	return (ops);
}

t_lst	gen_ops(t_ps_array arr, t_ps b, int b_rots, t_ps_node *node)
{
	t_lst	ops;
	int		i;
	int		j;

	j = 0;
	i = 0;
	ops = NULL;
	node->a_cost = find_range(node->value, arr.base, 0, arr.size - 1);
	if (b_rots > (int)(b->len - 1) / 2)
		b_rots -= (int)b->len;
	node->b_cost = b_rots;
	while (i < (int)ABS(node->a_cost) || j < (int)ABS(node->b_cost))
	{
		if (i++ < (int)ABS(node->a_cost))
			ft_lstpush(&ops, op_as_node(node->a_cost > 0 ? OP_ROT : OP_RROT,
											APPLY_ON_A));
		if (j++ < (int)ABS(node->b_cost))
			ft_lstpush(&ops, op_as_node(node->b_cost > 0 ? OP_ROT : OP_RROT,
											APPLY_ON_B));
	}
	ft_lstpush(&ops, op_as_node(OP_PUSH, APPLY_ON_A));
	return (compress_ops(ops));
}

void	adjust_stack(t_ps a, t_lst *ops, t_flags *flags)
{
	t_ps_array	arr;
	int			n_rots;
	int			min;
	int			max;
	bool		is_up;

	if (ps_issorted(a, NULL))
		return ;
	is_up = true;
	arr = ps_vals_asarray(a);
	min = binary_search_min(arr.base, 0, arr.size - 1);
	max = (min == 0) ? (int)arr.size - 1 : min - 1;
	n_rots = (int)arr.size - 1 - min - 1;
	if (flags->verbose)
		dump_state(a, NULL, NULL, NULL);
	if ((is_up = (n_rots >= 0)))
		n_rots = max + 1;
	else
		n_rots = ABS(n_rots);
	while (n_rots--)
		op_save(OP_INIT(is_up ? OP_ROT : OP_RROT, APPLY_ON_A),
				ops, a, NULL);
	if (flags->verbose)
		dump_state(a, NULL, NULL, NULL);
	free(arr.base);
}

enum e_ops_list_states
{
	FRONT_OPS,
	REAR_OPS,
	OPTIMAL_OPS
};

void		dump_node(t_qnode *e)
{
	t_ps_node *node;

	if (!e)
		return ;
	node = e->blob;
	ft_dprintf(2, "   %{green_fg}%+4d%{yellow_fg}"
			   "[%+.2d]%{blue_fg}[%+.2d]%{reset}\n",
			   node->value, node->a_cost, node->b_cost);
}

void	push_swap(t_ps a, t_ps b, t_lst *ops, t_flags *flags)
{
	t_ps_node	*node;
	t_ps_array	arr;
	t_qnode		*walk[2];
	t_lst		tmp[3];
	int			b_rots;

	tmp[OPTIMAL_OPS] = NULL;
	ps_sort_few(a, b, ops);
	ft_bzero(tmp, 3 * sizeof(t_lst));
	while (b->len)
	{
		b_rots = 0;
		walk[FRONT_OPS] = b->stack->head->next;
		walk[REAR_OPS] = b->stack->tail->prev;
		/* queue_iter(b->stack, dump_node); */
		/* ft_putendl("---"); */
		/* queue_iter(a->stack, dump_node); */
		/* getchar(); */
		arr = ps_vals_asarray(a);
		while (true)
		{
			/* ft_printf("+"); */
			tmp[FRONT_OPS] = gen_ops(arr, b, b_rots++, walk[FRONT_OPS]->blob);
			take_best_ops(&tmp[OPTIMAL_OPS], &tmp[FRONT_OPS], &node,
						  walk[FRONT_OPS]->blob);

			tmp[REAR_OPS] = gen_ops(arr, b, b->len - b_rots,
										walk[REAR_OPS]->blob);
			take_best_ops(&tmp[OPTIMAL_OPS], &tmp[REAR_OPS], &node,
						  walk[REAR_OPS]->blob);

			if ((int)ft_lstlen(tmp[OPTIMAL_OPS]) <= b_rots + 1)
				break ;

			/* two cases, either or even */
			if (walk[FRONT_OPS]->next == walk[REAR_OPS]
					|| walk[FRONT_OPS] == walk[REAR_OPS])
				break;

			walk[FRONT_OPS] = walk[FRONT_OPS]->next;
			walk[REAR_OPS] = walk[REAR_OPS]->prev;
		}
		if (flags->verbose)
			dump_state(a, b, tmp[OPTIMAL_OPS], node);
		free(arr.base);
		append_ops(a, b, ops, &tmp[OPTIMAL_OPS]);
	}
	adjust_stack(a, ops, flags);
}

int		main(int argc, char **argv)
{
	t_ps	ps_a;
	t_ps	ps_b;
	t_lst	ops;
	t_flags	flags;

	if (!(ps_a = read_args(argc, argv, &flags)))
		return (EXIT_FAILURE);
	ps_b = ps_alloc('B', ps_a->size);
	ops = NULL;
	if (!ps_issorted(ps_a, ps_b))
	{
		if (flags.verbose)
			dump_state(ps_a, ps_b, NULL, NULL);
		while (ps_a->len > FEW_ELEMENTS)
			op_save(OP_INIT(OP_PUSH, APPLY_ON_B), &ops, ps_a, ps_b);
		push_swap(ps_a, ps_b, &ops, &flags);
		dump_ops(ops, &flags);
		ft_lstdel(&ops, lstdel_helper);
	}
	ps_del(&ps_a);
	ps_del(&ps_b);
	return (EXIT_SUCCESS);
}
