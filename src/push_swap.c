/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:18:20 by archid-           #+#    #+#             */
/*   Updated: 2019/11/02 09:51:25 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "reader.h"

#define ONE_THIRD(foo)								((foo) / 3)

t_dlst	split_stack_a(t_ps a, t_ps_node *mids)
{
	t_dlst		walk;
	t_ps_node	*node;

	walk = a->head;
	while (walk)
	{
		if ((node = (t_ps_node *)walk->blob)->val)
		{

		}
		walk = walk->next;
	}
	return (NULL);
}

t_range	helper_in_range(t_val target, t_dlst node)
{

}

void	push_to_upper(t_ps b, t_ps_node *val)
{

}

void	push_to_lower(t_ps b, t_ps_node *val)
{

}

void	fill_stack_b(t_ps a, t_ps b, t_ps_node *mids)
{
	t_ps_node	*target;
	t_dlst		splited;
	t_dlst		walk;
	int			check;
	int			val;

	/* mids = find_mids(a); */
	walk = a->head;
	while (walk)
	{
		target = (t_ps_node *)walk->blob;
		check = helper_in_range(target->val, splited);
		if (check == RANGE_LOW)
			push_to_lower(b, target);
		else if (check == RANGE_MID)
			push_to_upper(b, target);
		walk = walk->next;
	}
}

t_ps_node	*find_mids(t_ps a_sorted, t_ps_node *mids)
{
	/* look for 1/2 and 2/3 */
	size_t i;
	short index;
	t_dlst walk;

	i = 0;
	index = 0;
	walk = a_sorted->head;
	while (walk)
	{
		while (i++ < ONE_THIRD(a_sorted->size))
			walk = walk->next;
		mids[index] = *GET_PS_NODE(walk);
		if (index++)
			walk = NULL;
	}
	return (mids);
}

/* NOTE: for the moment solve the main case: 8 5 6 3 1 2 */
void	push_swap(t_ps a, t_ps b)
{
	t_ps		sorted_a;
	t_ps_node	mids[2];

	sorted_a = ps_mergesort(a);
	fill_stack_b(a, b, find_mids(sorted_a, mids));

}

static void		helper_node_dump(t_dlst e)
{
	char *s_range;

	if (!e)
		return ;
	/* TODO: update repo's libft */
	if (GET_PS_NODE(e)->range == RANGE_LOW)
		s_range = "SMALL";
	else if (GET_PS_NODE(e)->range == RANGE_MID)
		s_range = "MID";
	else
		s_range = "HIGH";
	printf("(%p| ord: %d, val: %d, range: %s)\n", e,
		   GET_PS_NODE(e)->ord, GET_PS_NODE(e)->val, s_range);
}

int main(int argc, char **argv)
{
	t_ps		ps_a, ps_b;
	t_ps		sorted;
	t_ps_node	mids[2];
	t_dlst		walk;

	/* t_lst	ops; */
	/* t_lst	walk; */
	/* bool	failed; */
	/* t_op	*op; */

	if (!(ps_a = read_args(argc, argv)))
		return (EXIT_FAILURE);
	sorted = ps_mergesort(ps_a);
	ft_dlstiter(sorted->head, helper_node_dump);
	ft_putendl("//");
	walk = sorted->tail;
	while (walk)
	{
		helper_node_dump(walk);
		walk = walk->prev;
	}
	ps_del(&ps_a);

	/* find_mids(sorted, mids); */

	return (0);
}
