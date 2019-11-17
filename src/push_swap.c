/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:18:20 by archid-           #+#    #+#             */
/*   Updated: 2019/11/17 00:16:46 by archid-          ###   ########.fr       */
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

int		find_fit(t_lst node, t_lst *arrlst, size_t low, size_t high)
{
	size_t mid;
	size_t i;

	i = 0;
	mid = (low + high) / 2;		/* this is the relative mid,
								   not the mid of the array */
	if (NODE_ORDER(arrlst[mid], ==, node))
		return mid;
	/* rot to right */
	else if (NODE_ORDER(arrlst[low], >, arrlst[high]))
	{
		/*

		  NOTE: A is sorted in accesnding order, looking for 6

		   A is not rotated, B is rotated by 4 steps. Both have distinct
		   integers (possibly negative too). thus, mid is preserved with
		   index, otherwise, we shall think of duplicates as one chunk.
		   by changing the high and low correspodenly.

		   - mid of A is 8, where A[8] = 8.
		   - mid of B is 3, where B[8] = 3 but the relative mid of A is
		     at index [13]

		   now, notes about the rotation and the mid since the rotation,
		   i guess we can know which side to go to based on the last one.

		   we look for e, where e == 6,

		   A: 0  1  2  3  4  5 6 7 8 9 10 11 12 13 14 15 16 17


		   // reverse rotation (rr) right/down
		   B: 13 14 15 16 17 0 1 2 3 4 5  6  7  8  9  10 11 12
		                           ^            ^

								  mid      relative mid

		   ------------------------v-----------------------
		   // normal rotation (r)
		   C: 5  6  7  8  9 10 11 12 13 14 15 16 17 0 1 2 3 4
		   left/up
		               ^
				  relative mid

		   // Part II

		   steps of the process
		   ~~~~~~~~~~~~~~~~~~~~~~~

		   #0 - calling binary_search_rot, we find out that low is bigger than high, thus it was a
		   right side rotation. the sorted part is the one on the left, while right side is not.
		   this is caused by the shift of mid to right side.
		   we shall see which side of the two the search key is in. if found on the left.
		   we shall check in which side it falls.
		   if it's between B[low] and B[mid], then do a plain binary search since we already know
		   that the left region is sorted (B[low] and B[mid]).

		   A[i]  \  i   | shift | low | mid | high|
		   -------------+-------+-----+-----+-----+
		     B          | right | 13  | 3   |  12 |
			 C          | left  | 5   | 12  |  4  |

		   #1 - calling

		   A[i]  \  i   | low | mid | high|
		   -------------+-----+-----+-----+
		     B
			 C

		   // Part I

		   this is a right side rotation, meaning that the left range is
		   unsorted. we shall focus on the right range. so that right,
		   right seems in place. (i guess that left rotation is the same case)

		   now to actually find the mid, we shall find which side is the
		   one sorted.

		   now the mid of b will lead to which side to take, so after we shall
		   find the range of operation. first, see if low < mid, if so then pick
		   and we know that the order is ascending, thus: the missed part is
		   the on the right, we shall take the left side.

		   binary_search_rot:

		   given:

				a search key element, e.
				three indices low, mid and high.

		   if (MAX(e, B[low]) == B[low]) && (MIN(e, B[mid]) == B[mid])
				high = mid
				call binary_search(b, low, mid)
		   else
		       low = mid + 1
			   recall binary_search_rot(b, mid, high)

		   the example abive is in case of a rotation
		   while on the right it will change the side of working

		   if (MAX(e, B[mid]) == e && MIN(e, B[high]) == e)


		   -------------
		   #1

		   e == 6
		   B[low] == 13 and B[high] == 12, thus array is rotated to the right
		   B[]







		*/

		if ()
		low = mid;

	}
	else
	{
		/* rot to left  */

	}
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
	while (a->len)
	{
		walk = a->stack;
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
