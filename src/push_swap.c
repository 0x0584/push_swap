/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:18:20 by archid-           #+#    #+#             */
/*   Updated: 2019/11/21 00:16:15 by archid-          ###   ########.fr       */
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

#define FEW_ELEMENTS								(3)

void	ps_sort_few(t_ps a, t_ps b, t_lst *ops)
{
	void	**arrlst;
	size_t	size;

	if (a->size == 2)
	{
		if (GET_NODE(a->stack)->value > GET_NODE(a->stack->next)->value)
			op_save(OP_INIT(OP_SWAP, APPLY_ON_A), ops, a, b);
	}
	else if (a->size == FEW_ELEMENTS)
	{
		/* compare the three elements */
	}

}


# define AS_INT(ptr)				*(int *)ptr

size_t binary_search(void *key, void **arr, size_t low, size_t high)
{
	size_t mid;

	mid = (low + high) / 2;
	while (low < high)
	{
		ft_printf("KEY(%d)\n[%d] = %d (low)\n[%d] = %d (mid)\n"
				  "[%d] = %d (high)\n",
				  AS_NODE(key)->value,
				  low, AS_NODE(arr[low])->value,
				  mid, AS_NODE(arr[mid])->value,
				  high, AS_NODE(arr[high])->value);
		/* getchar(); */
		if (AS_NODE(key)->value == AS_NODE(arr[mid])->value)
			return (mid);
		else if (AS_NODE(key)->value < AS_NODE(arr[mid])->value)
			high = mid;
		else
			low = mid;
		mid = (low + high) / 2;
	}
	return (mid);
}

void	find_split(t_ps ps, size_t *min_index, size_t *max_index);
bool	node_order(t_ps_node *left, t_ps_node *middle, t_ps_node *right);
void	lstdel_helper(void *content, size_t content_size);

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

t_lst	find_ops(t_ps a, t_ps b, int b_rots, t_lst node)
{
	t_lst	ops;
	void	**arr;
	size_t	size;

	size_t low;
	size_t high;
	int		a_rots;

	bool is_up;
	bool flag;

	ops = NULL;
	arr = ft_lst_content_asarray(a->stack, &size);
	a_rots = 0;

	find_split(a, &low, &high);
	flag = false;
	if (low == 0 && high == (size - 1)) /* sorted */
	{

		while (a_rots++ <= (int)(a->len / 2))
		{
			if (a_rots == 0 &&
				(ps_node_cmp(node->content, arr[low], CMP_LT)
					|| ps_node_cmp(node->content, arr[high], CMP_GT)))
				break ;
			else if (ps_node_cmp(node->content, arr[low + a_rots], CMP_GT)
					 && ps_node_cmp(node->content,
									arr[low + a_rots + 1], CMP_LT))
			{
				is_up = true;
				break ;
			}
			else if (ps_node_cmp(node->content, arr[high], CMP_LT)
					 && ps_node_cmp(node->content, arr[high - 1], CMP_GT))
			{
				is_up = false;
				break ;
			}
			a_rots++;
		}
	}
	else
	{
		/* not sorted */
	}

	bool on_top;

	/* n_rots = find_fit(node, arr, 0, b->len - 1); */
	while (true)
	{
		if (b_rots--)
		{

		}
		op_save(OP_INIT(OP_ROT, APPLY_ON_A), &ops, a, b);
	}
	op_save(OP_INIT(OP_PUSH, APPLY_ON_A), &ops, a, b);
	return (compress_ops(ops));
}


void	push_swap(t_ps a, t_ps b)
{
	t_lst ops;
	t_lst walk;
	t_lst tmp_ops;
	t_lst optimal_ops;
	int n_rots;

	if (ps_issorted(a, b))
		return ;

	ops = NULL;
	n_rots = 0;
	optimal_ops = NULL;

	/* push everything to b and leave only elements. only check if they're
	 * in desending order. if they are, correct order. prioritize ranges,
	 *
	 * suppose given an array, A_{0} = [5, 100, 2], it is sorted and rotated.
	 * A_{+1} = [2, 5, 100]. How ever giving B
	 */

	/* either we have few */
	if (a->size <= FEW_ELEMENTS)
		ps_sort_few(a, b, &ops);

	/* or push everything to b and leave few */
	while (a->len - FEW_ELEMENTS)
		op_save(OP_INIT(OP_PUSH, APPLY_ON_B), &ops, a, b);
	ps_sort_few(a, b, &ops);


	while (b->len)
	{
		walk = b->stack;
		while (walk)
		{
			size_t imin, imax;

			tmp_ops = find_ops(a, b, n_rots++, walk->content);
			if (ft_lstlen(tmp_ops) < ft_lstlen(optimal_ops))
			{
				ft_lstdel(&optimal_ops, lstdel_helper);
				optimal_ops = tmp_ops;
			}
			walk = walk->next;
		}
		/* do optimal ops */
	}
	ft_lstiter(ops, helper_op_dump);
	ft_lstdel(&ops, helper_op_free);

	ft_printf("FINAL RESULT: %s", ps_issorted(a, b) ? "OK" : "KO");
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


	find_split(ps_a, &imin, &imax);

	ft_printf("(min index: %d max index: %d)\n", imin, imax);
	ps_del(&ps_a);

	/* int arr[] = {4,5,6,7,8,9,0,1,2,3}; */
	/* test(); */


	return (EXIT_SUCCESS);

}
