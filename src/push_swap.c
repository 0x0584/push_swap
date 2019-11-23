/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:18:20 by archid-           #+#    #+#             */
/*   Updated: 2019/11/23 01:05:48 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "reader.h"
#define AS_NODE(obj)							((t_ps_node *)obj)
#define FEW_ELEMENTS							(3)

/* test passed: 0 9 4 11 8 7 55 44 33 22 101 402 -1 */
void	op_save(bool commit, t_op op, t_lst *ops, t_ps a, t_ps b)
{
	if (commit && !op_apply(op, a, b))
	{
		ft_dprintf(2, "%{yellow_fg}note: cannot apply operation!\n%{reset}");
		op_dump(op);
	}
	ft_lstpush(ops, ft_lstnew(&op, sizeof(t_op)));
}

void	find_split(t_ps ps, size_t *min_index, size_t *max_index);
bool	node_order(t_ps_node *left, t_ps_node *middle, t_ps_node *right);
void	lstdel_helper(void *content, size_t content_size);

void	ps_sort_few(t_ps a, t_ps b, t_lst *ops)
{
	void	**arrlst;
	size_t	size;

	if (a->size == 2)
	{
		if (GET_NODE(a->stack)->value > GET_NODE(a->stack->next)->value)
			op_save(true, OP_INIT(OP_SWAP, APPLY_ON_A), ops, a, b);
	}
	else if (a->size == FEW_ELEMENTS)
	{
		/* compare the three elements */
	}
}

/* FIXME: optimize when possible
 *
 * when length of stack is two, either use r or rr depending on the optimal
 */
t_lst	compress_ops(t_ps a, t_ps b, t_lst ops)
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

int		*ps_vals_asarray(t_ps ps, size_t *size)
{
	int		*arr;
	size_t	i;
	t_lst	walk;

	if (!ps || !(arr = ALLOC(int *, ft_lstlen(ps->stack) + 1, sizeof(int))))
		return (NULL);
	walk = ps->stack;
	i = 0;
	while (walk)
	{
		arr[i++] = AS_NODE(walk->content)->value;
		walk = walk->next;
	}
	if (size)
		*size = i;
	return (arr);
}

int		find_fit(t_ps a, t_ps_node *node)
{
	t_lst	ops;
	int		*arr;
	size_t	size;
	int		n_rots;

	ops = NULL;
	arr = ps_vals_asarray(a, &size);
	n_rots = binary_search_range(node->value,
								 arr, 0, size - 1, ascending_order);
	free(arr);
	/* while (true) */
	/* { */
	/* 	if (b_rots--) */
	/* 	{ */

	/* 	} */
	/* 	op_save(OP_INIT(OP_ROT, APPLY_ON_A), &ops, a, b); */
	/* } */
	/* op_save(OP_INIT(OP_PUSH, APPLY_ON_A), &ops, a, b); */
	return n_rots;
}

t_lst	gen_ops(t_ps_node *node)
{
	t_lst	ops;
	int		i;
	int		j;

	j = 0;
	i = 0;
	ops = NULL;

	ft_printf("generating ops for %{red_fg}(%d)%{reset}\n"
			  " >> rots on stack A [%d] rots on stack B [%d]",
			  node->value, node->a_cost, node->b_cost);
	// getchar();


	while (i < (int)ABS(node->a_cost) || j < (int)ABS(node->b_cost))
	{

		if (i++ < (int)ABS(node->a_cost))
			op_save(false, OP_INIT(node->a_cost > 0 ? OP_ROT : OP_RROT,
								   APPLY_ON_A), &ops, NULL, NULL);
		if (j++ < (int)ABS(node->b_cost))
			op_save(false, OP_INIT(node->b_cost > 0 ? OP_ROT : OP_RROT,
								   APPLY_ON_B), &ops, NULL, NULL);
		ft_printf("ops..\n");
		// getchar();
	}
	op_save(false, OP_INIT(OP_PUSH, APPLY_ON_A), &ops, NULL, NULL);

	ft_printf("dumped ops: \n\n");
	ft_lstiter(ops, helper_op_dump);
	// getchar();

	/* or should all it sync_ops? */
	/* return (compress_ops(ops)) */
	return (compress_ops(NULL, NULL, ops));
}

void	adjust_stack(t_ps a, t_lst *ops)
{
	int		*arr;
	size_t	size;
	size_t	n_rots;
	bool is_up;

	is_up = true;
	arr = ps_vals_asarray(a, &size);
	n_rots = binary_search_find_min(arr, 0, size - 1, ascending_order);

	if (n_rots > a->len / 2)
	{
		n_rots = a->len / 2 - (n_rots - (a->len / 2)) - 1;
		is_up = false;
	}
	ft_printf("nrots to get min: %d\n", n_rots);
	while (n_rots--)
		op_save(true, OP_INIT(is_up ? OP_ROT : OP_RROT, APPLY_ON_A),
				ops, a, NULL);
}


void	push_swap(t_ps a, t_ps b)
{
	t_lst ops;
	t_lst walk;
	t_lst tmp_ops;
	t_lst optimal_ops;
	int b_rots;
	int a_rots;

	if (ps_issorted(a, b))
		return ;

	ops = NULL;
	optimal_ops = NULL;

	/* either we have few */

	if (a->size <= FEW_ELEMENTS)
		return ps_sort_few(a, b, &ops);

	/* or push everything to b and leave few */
	while (a->len - FEW_ELEMENTS)
		op_save(true, OP_INIT(OP_PUSH, APPLY_ON_B), &ops, a, b);
	ps_sort_few(a, b, &ops);

	while (b->len)
	{
		walk = b->stack;
		a_rots = 0;
		b_rots = 0;
		tmp_ops = NULL;

		ft_printf(" ----- current ops -----\n\n");
		ft_lstiter(ops, helper_op_dump);
		// getchar();
		dump_stacks(a, b);
		// getchar();

		while (walk)
		{
			/* size_t imin, imax; */

			a_rots = find_fit(a, walk->content);
			GET_NODE(walk)->a_cost = a_rots;

			ft_printf("\n%d rots to get %d from B.\n",
					  b_rots, GET_NODE(walk)->value);

			ft_printf(" >> %d rots to place %d in A\n",
					  a_rots, GET_NODE(walk)->value);

			GET_NODE(walk)->b_cost = b_rots++;

			tmp_ops = gen_ops(walk->content);

			if (!optimal_ops)
				optimal_ops = tmp_ops;
			else if (ft_lstlen(tmp_ops) < ft_lstlen(optimal_ops))
			{
				ft_lstdel(&optimal_ops, lstdel_helper);
				optimal_ops = tmp_ops;
			}

			if (ft_lstlen(optimal_ops) <= 2)
				break;

			// getchar();

			walk = walk->next;
		}
		/* do optimal ops */
		ft_printf("%{green_fg}applying ops%{reset}\n");
		walk = optimal_ops;
		while (walk)
		{
			op_save(true, *(t_op *)walk->content, &ops, a, b);
			walk = walk->next;
		}
		// getchar();
		ft_lstdel(&optimal_ops, lstdel_helper);
	}

	ft_printf(" << maybe rotated stacks >>\n");
	dump_stacks(a, b);
	ft_printf(" << final stacks >>\n");
	adjust_stack(a, &ops);
	dump_stacks(a, b);

	ft_printf(" << final operations >>\n");

	ft_lstiter(ops, helper_op_dump);
	ft_lstdel(&ops, helper_op_free);

	ft_printf("FINAL RESULT: %s\n", ps_issorted(a, b) ? "OK" : "KO");
}



/* ascending order
 * Complexity: O(N) */

void	find_split(t_ps ps, size_t *min_index, size_t *max_index)
{
	void	**arr;
	size_t	i;
	size_t	size;

	if (!ps || !ps->stack || !(arr = ft_lst_content_asarray(ps->stack, &size)))
		return ;
	i = 0;
	*min_index = 0;
	while (i < size)
	{
		if (AS_NODE(arr[i])->value < AS_NODE(arr[*min_index])->value)
			*min_index = i;
		i++;
	}
	*min_index = i;
	*max_index = (i + size - 1) % size;
}

bool	node_order(t_ps_node *left, t_ps_node *middle, t_ps_node *right)
{
	if (!left || !middle || !right)
		return (false);
	return (left->value < middle->value && middle ->value < right->value);
}


int		main(int argc, char **argv)
{
	t_ps ps_a;
	t_ps ps_b;

	size_t imin;
	size_t imax;

	if (!(ps_a = read_args(argc, argv)))
		return EXIT_FAILURE;
	ps_b = ps_alloc('b', ps_a->size);

	/* dump_stacks(ps_a, ps_b); */

	/* op_dorot(ps_a, false); */
	/* dump_stacks(ps_a, ps_b); */
	/* // getchar(); */

	push_swap(ps_a, ps_b);

	/* find_split(ps_a, &imin, &imax); */
	/* ft_printf("(min index: %d max index: %d)\n", imin, imax); */

	ps_del(&ps_a);
	ps_del(&ps_b);

	/* int arr[] = {4,5,6,7,8,9,0,1,2,3}; */
	/* test(); */

	return (EXIT_SUCCESS);

}
