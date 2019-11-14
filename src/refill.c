/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refill.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:07:45 by archid-           #+#    #+#             */
/*   Updated: 2019/11/14 17:12:33 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "ft_printf.h"

void	ps_sort_remainder(t_ps a, t_lst *ops)
{
	t_op op;

	/*
	   for the moment, only two elements left, so we shlal swap them
	  once, he told me that we can find a sort for 6 elements
	*/
	t_ps_node *head;
	t_ps_node *tail;

	head = GET_PS_NODE(a->head);
	tail = GET_PS_NODE(ft_dlst_gettail(a->head));
	if (head->val > tail->val)
	{
		/* here I shall either use swap or rotation */
		/* maybe bruteforce on less than 6 elements */
		op_dorot(a, true);
		op = OP_INIT(OP_ROT, APPLY_ON_A);
		ft_lstpush(ops, ft_lstnew(&op, sizeof(t_op)));
	}
}

int		ps_whichturn(t_ps ps)
{
	int turn;
	t_dlst walk;

	turn = -1;
	walk = ps->head;
	while (walk)
	{
		if (turn < GET_PS_NODE(walk)->turn)
			turn = GET_PS_NODE(walk)->turn;
		walk = walk->next;
	}
	return turn;
}

t_range		ps_current_range(t_ps b, int turn)
{
	t_dlst walk;

	/* walk = b->head; */
	/* while (walk) */
	/* { */
	/* 	if (GET_PS_NODE(walk)->turn == turn */
	/* 			&& GET_PS_NODE(walk)->range == RANGE_LOW) */
	/* 		return RANGE_LOW; */
	/* 	walk = walk->next; */
	/* } */
	return (RANGE_HIGH);
}

int		ps_find_largest_node(t_ps ps)
{
	t_dlst	walk;
	int		i;
	int		index;
	int		turn;
	t_range range;
	t_val max;
	t_ps_node *node;

	if (!ps)
		return (-1);

	i = 0;
	index = -1;
	walk = ps->head;
	turn = ps_whichturn(ps);
	range = ps_current_range(ps, turn);
	max = GET_PS_NODE(walk)->val;
	while (walk)
	{
		/* if (GET_PS_NODE(walk)->turn == turn */
		/* 		&& GET_PS_NODE(walk)->range == range */
		/* 		&& GET_PS_NODE(walk)->val >= max) */
		/* { */
		/* 	node = GET_PS_NODE(walk); */
		/* 	max = node->val; */
		/* 	index = i; */
		/* } */
		i++;
		walk = walk->next;
	}
	ft_dprintf(2, "index of the largest node (%{cyan_fg}%d%{reset}) "
			   "is: %{yellow_fg}%d%{reset}\n", index, node->val);
	return (index);
}

void	ps_refill(t_ps a, t_ps b, t_lst *ops)
{
	int		turn;
	int		rotate_count;
	bool	is_up;
	bool	is_firsttime;
	t_ps_node *head, *tail;
	t_op op;

	if (!a || !b)
		return ;
	is_up = true;
	turn = 0;
	rotate_count = 0;
	ps_sort_remainder(a, ops);
	dump_stacks(a, b);
	is_firsttime = true;
	ft_dprintf(2, "refilling!\n");
	/* getchar(); */
	while (b->len)
	{
		head = GET_PS_NODE(b->head);
		tail = GET_PS_NODE(ft_dlst_gettail(b->head));
		/* tail = GET_PS_NODE(b->tail); */
		ft_dprintf(2, "{%d} head: %d tail: %d\n", turn++,
					head->val, tail->val);
		int node_index = ps_find_largest_node(b);

		if (!b->len || (is_up = (node_index <= (int)b->len / 2)))
			rotate_count = node_index;
		else
			rotate_count = (int)b->len % node_index;
		ft_dprintf(2, "node index %d \n half b->len %d \n rotation count %d\n",
				   node_index, (int)b->len / 2, rotate_count);
		ft_dprintf(2, " >> rotate_count %d and rotation is %s\n",
					rotate_count, is_up ? "normal" : "reversed");
		/* getchar(); */
		while (rotate_count--)
		{
			op_dorot(b, is_up);
			op = OP_INIT(is_up ? OP_ROT : OP_RROT, APPLY_ON_B);
			ft_lstpush(ops, ft_lstnew(&op, sizeof(t_op)));
		}
		op_dopsh(a, b);
		op = OP_INIT(OP_PUSH, APPLY_ON_A);
		ft_lstpush(ops, ft_lstnew(&op, sizeof(t_op)));
		dump_stacks(a, b);
		ft_dprintf(2, "after pushing\n");
		/* getchar(); */
	}
	/* ft_dprintf(2, "splitting again"); */
	/* ps_split_ranges(b, a, ops); */
}

// IDEA: split into ranges based on the input size
