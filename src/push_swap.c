/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:18:20 by archid-           #+#    #+#             */
/*   Updated: 2019/11/18 03:11:20 by archid-          ###   ########.fr       */
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

# define AS_NODE(obj)					((t_ps_node *)obj)
# define NODE_VALUE(obj)				(AS_NODE(obj->content)->value)
# define NODE_ORDER(u, ord, v)			(NODE_VALUE(u) ord NODE_VALUE(v))

/* FIXME: add arrlst to t_ps */

/*
   return the number of rotations

   given three integers low = 0, mid = 4, high = 8 and an array A_{0},
   sorted, in asending order. we can hold this if we use pb `size' times.
   and use check on stack A instead.

   A_{0}  = [1, 2, 3, 4, 5, 6, 7, 8, 9]
	 - A_{0}[low] = 0, A_{0}[mid] = 5, A_{0}[high] = 9

   given i \in Z, where A_{i}:

     - if i == 0, then it means that array A has not rotated.
	   ie, sorted-mid is at it's place.
	 - if i > 0, means that the mid is shifted to right.
	 - i < 0 means that it has been rotated at left.

   in case of A_{-3} = [4, 5, 6, 7, 8, 9, 1, 2, 3]
	 - A_{-3}[low] = 4, A_{-3}[mid] = 8, A_{-3}[high] = 3

   given a search key of (6), then we have the following

		- A_{-3}[low] > A{-3}[high]  ??
		- A_{-3}[mid] > A{-3}[value]

   NOTE: the question is, given all possible combinations of low, mid, high

		- A_{-3}[low] < A{-3}[high] && A_{-3}[mid] > A{-3}[high]
		- A_{-3}[low] < A{-3}[high] && A_{-3}[mid] > A{-3}[high]


   A_{+3} = [7, 8, 9, 1, 2, 3, 4, 5, 6]
	 - A_{+3}[low] = 7, A_{+3}[mid] = 2, A_{+3}[high] = 6

   A_{+4} = [6, 7, 8, 9, 1, 2, 3, 4, 5]
	 - A_{+4}[low] = 6, A_{+4}[mid] = 1, A_{+4}[high] = 5

   test cases:
   ~~~~~~~~~~~~~

    TODO: test on different rotations and search keys.

*/

int		find_fit(t_lst node, t_lst *arrlst, size_t low, size_t high)
{
	size_t mid;
	size_t i;

	i = 0;
	mid = (low + high) / 2;		/* this is the relative mid */
	/* while */
	return (0);
}

t_lst	find_ops(t_lst node, int index, t_ps b)
{
	t_lst	ops;
	t_lst	*arrlst;
	size_t	size;

	int		n_rots;

	ops = NULL;
	arrlst = ft_lst_asarray(b->stack, &size);
	n_rots = find_fit(node, arrlst, 0, b->len - 1);

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

	/* push everything to b and leave only elements. only check if they're
	 * in desending order. if they are, correct order. prioritize ranges,
	 *
	 * suppose given an array, A_{0} = [5, 100, 2], it is sorted and rotated.
	 * A_{+1} = [2, 5, 100]. How ever giving B
	 *
	 *
	 *
	 */
	while (a->len - 3)
		op_save(OP_INIT(OP_PUSH, APPLY_ON_B), &ops, a, b);
	while (b->len)
	{
		walk = b->stack;
		while (walk)
		{
			tmp_ops = find_ops(walk, index++, b);
			if (ft_lstlen(tmp_ops) < ft_lstlen(optimal_ops))
			{
				ft_lstdel(&optimal_ops, lstdel_helper);
				optimal_ops = tmp_ops;
			}
			walk = walk->next;
		}
	}
	ft_lstiter(ops, helper_op_dump);
	ft_lstdel(&ops, helper_op_free);

	ft_printf("FINAL RESULT: %s", ps_issorted(a, b) ? "OK" : "KO");
}

int		main(int argc, char **argv)
{
	t_ps ps_a;
	t_ps ps_b;

	/* if (!(ps_a = read_args(argc, argv))) */
	/* 	return (EXIT_FAILURE); */
	/* /\* push_swap(ps_a, ps_b = ps_alloc('b', ps_a->size)); *\/ */
	/* ps_del(&ps_a); */
	/* ps_del(&ps_b); */

	/* int arr[] = {4,5,6,7,8,9,0,1,2,3}; */
	/* test(); */
	return (0);
}
