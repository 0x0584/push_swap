/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:06:25 by archid-           #+#    #+#             */
/*   Updated: 2019/11/14 17:26:56 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "ft_printf.h"

t_ps_node	*ps_find_mids(t_ps a)
{
	short		index;
	t_dlst		walk;
	t_ps_node	*mid;
	t_ps		sorted_a;

	if (!a)
		return NULL;
	index = 0;
	sorted_a = ps_mergesort(a);
	walk = sorted_a->head;
	while (walk && index < (int)sorted_a->len / 2)
	{
		index++;
		walk = walk->next;
	}
	mid = GET_PS_NODE(walk);
	ft_dprintf(2, "%{yellow_fg}mid is %d%{reset}\n", mid->val);
	ps_del(&sorted_a);
	return mid;
}

/*
   this shall always pick the best way to get a node.
   ie, based on the distribution of the numbers, find
   the best way to pick them. That's the key to the highway!
*/

t_dlst	helper_takefrom(t_dlst node, int *index, int turn, bool is_head)
{
	t_dlst walk;

	walk = node;
	while (node)
	{
		if (GET_PS_NODE(node)->turn == turn)
			break ;
		*index += 1;
		node = is_head ? node->next : node->prev;
	}
	*index += !is_head;			/* reverse rotation */
	return (node);
}

// NOTE: on which operation to do
//
// preferes a over b since top only requires pb while bottom
// requires an additional rotation, but this have many cases:
//
// suppose we a == 1 and and b == 0, we can either use swap to
// retrieve from a, or rotate. This could be decided when
// optimizating stuff

#define SMALL_INDEX(foo)			(foo[0] <= foo[1] ? foo[0] : foo[1])

void	ps_takefrom_best(t_ps a, t_ps b, int turn, t_lst *ops)
{
	t_dlst	head;
	t_dlst	tail;
	int		index[3];

	ft_bzero(index, 3 * sizeof(int));
	head = helper_takefrom(a->head, &index[0], turn, true);
	tail = helper_takefrom(ft_dlst_gettail(a->head), &index[1], turn, false);
	ft_dprintf(2, "\nhead is %d far from top >> \t", index[0]);
	helper_node_dump(head); ft_dprintf(2, "\n");
	ft_dprintf(2, "tail is %d far from bottom >> \t", index[1]);
	helper_node_dump(tail); ft_dprintf(2, "\n\n");
#if DEBUG_SPLIT
	getchar();
#endif
	index[2] = SMALL_INDEX(index);
		while (index[2]--)
			op_dorot(a, SMALL_INDEX(index) == index[0]);
		op_dopsh(b, a);
}

bool	split_end(t_ps a, int prev_turn)
{
	t_dlst	walk;
	bool	end;

	end = false;
	walk = a->head;

	while (!end && walk)
	{
		end = (GET_PS_NODE(walk)->turn == prev_turn);
		walk = walk->next;
	}
	return (end);
}

void	ps_split_ranges(t_ps a, t_ps b, t_lst *ops)
{
	int	turn;

	turn = ps_find_ranges(a);
	while (turn--)
	{
		ft_dprintf(2, "%{red_fg}splitting on turn {%d}%{reset}\n", turn);
		while (split_end(a, turn))
		{
			ps_takefrom_best(a, b, turn, ops);
			dump_stacks(a, b);
#if DEBUG_SPLIT
			getchar();
#endif
		}
	}
}
