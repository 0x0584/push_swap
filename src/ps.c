/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:22:14 by archid-           #+#    #+#             */
/*   Updated: 2019/11/06 02:20:40 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"
#include "op.h"
#include "ft_printf.h"

void	ps_dump(t_ps ps)
{
	t_dlst		walk;
	t_ps_node	*node;

	if (!ps)
		return ;
	ft_dprintf(2, "stack: %c[%zu/%zu]\n------------------\n",
			ps->symb, ps->len, ps->size);
	walk = ps->head;
	while (walk)
	{
		node = (t_ps_node *)walk->blob;
		ft_dprintf(2, "{%p/%d: %d}\n", walk, node->ord, node->val);
		walk = walk->next;
	}
	ft_dprintf(2, "------------------\n");
}

t_ps	ps_alloc(char symb, size_t size)
{
	t_ps ps;

	if (!(ps = ALLOC(t_ps, 1, sizeof(struct s_ps_ds))))
		return (NULL);
	ps->symb = symb;
	ps->size = size;
	return (ps);
}

void	ps_del(t_ps *aps)
{
	if (!SAFE_PTRVAL(aps))
		return ;
	ft_dlstdel(lstdel_helper, &(*aps)->head);
	free(*aps);
	*aps = NULL;
}

bool	ps_issorted(t_ps ps_a, t_ps ps_b)
{
	t_dlst walk;

	if (!ps_a || !ps_a->head || (ps_b && ps_b->head))
		return (false);
	/* ps_dump(ps); */
	walk = ps_a->head;
	while (walk->next)
	{
		if (((t_ps_node *)walk->blob)->val
				> ((t_ps_node *)walk->next->blob)->val)
			return (false);
		walk = walk->next;
	}
	return (true);
}

t_ps	ps_clone(t_ps const ps)
{
	t_ps	duped;
	t_dlst	node;
	t_dlst	walk;

	duped = ps_alloc('Y', ps->size); /* deal with it my man! */
	duped->size = ps->size;
	duped->len = ps->len;
	walk = ps->head;
	while (walk)
	{
		node = ft_dlstpush(&duped->head, ft_dlstnew(walk->blob, walk->size));
		if (!walk->next)
			duped->tail = node;
		walk = walk->next;
	}
	return (duped);
}

int		ps_node_cmp(t_dlst foo, t_dlst bar)
{
	if (!foo || !bar)
		return (-1);
	return (GET_PS_NODE(bar)->val - GET_PS_NODE(foo)->val);
}

t_ps	ps_mergesort(t_ps ps)
{
	t_ps sorted;

	sorted = ps_clone(ps);
	ft_dlstmergesort(&sorted->head, ps_node_cmp);
	sorted->tail = ft_dlst_gettail(sorted->head);
	return (sorted);
}

t_range		ps_whichrange(t_val val, t_ps_node *mids)
{
	if (!mids)
		return (RANGE_NA);
	/* TODO: check whether mid is included or excluded */
	if (val < mids[0].val)
		return (RANGE_LOW);
	else if (val >= mids[0].val && val < mids[1].val)
		return (RANGE_MID);
	return (RANGE_HIGH);
}

void	ps_find_mids(t_ps a, t_ps_node *mids)
{
	/* look for 1/2 and 2/3 */
	size_t	i;
	short	index;
	t_dlst	walk;
	t_ps	sorted_a;

	if (!a || !mids)
		return ;
	index = 0;
	sorted_a = ps_mergesort(a);
	/* ft_dlstiter(sorted_a->head, helper_node_dump); */
	/* ft_putendl("dumped!"); */
	/* getchar(); */
	walk = sorted_a->head;
	while (walk)
	{
		i = 0;
		while (i++ < ONE_THIRD(a->len))
			walk = walk->next;
		mids[index] = *GET_PS_NODE(walk);
		if (index++) walk = NULL;
	}
	ft_dprintf(2, "lower mid: %d higher mid: %d\n", mids[0].val, mids[1].val);
	/* getchar(); */
	ps_del(&sorted_a);
}

/* TODO: check intra access tomorrow! */

void	ps_takefrom_best(t_ps a, t_ps b, t_lst *ops)
{
	t_ps_node	*head;
	t_ps_node	*tail;
	t_op		op;		/* HERE EITHER HEAD OR TAIL */
	bool		is_up;

	head = GET_PS_NODE(a->head);
	tail = GET_PS_NODE(ft_dlst_gettail(a->head));
	ft_dprintf(2, "Current node"); helper_node_dump(a->head); ft_dprintf(2, "\n");
	if (head->range == RANGE_LOW || head->range == RANGE_MID)
	{
		op_dopsh(b, a);
		op = OP_INIT(OP_PUSH, APPLY_ON_B);
		ft_lstpush(ops, ft_lstnew(&op, sizeof(t_op)));
	}
	if (head->range == RANGE_LOW && b->len > 1)
	{
		op_dorot(b, true);
		op = OP_INIT(OP_ROT, APPLY_ON_B);
		ft_lstpush(ops, ft_lstnew(&op, sizeof(t_op)));
	}
	if (head->range == RANGE_HIGH)
	{
		is_up = (tail->range == RANGE_LOW
					|| tail->range == RANGE_HIGH);
		op_dorot(a, is_up);
		op = OP_INIT(is_up ? OP_ROT : OP_RROT, APPLY_ON_A);
		ft_lstpush(ops, ft_lstnew(&op, sizeof(t_op)));
	}
}

void	ps_setranges(t_ps a, int turn, t_ps_node *mids)
{
	t_dlst walk;

	walk = a->head;
	while (walk)
	{
		GET_PS_NODE(walk)->turn = turn;
		GET_PS_NODE(walk)->range = ps_whichrange(GET_PS_NODE(walk)->val, mids);
		walk = walk->next;
	}
}

void	ps_split_ranges(t_ps a, t_ps b, t_lst *ops)
{
	t_ps_node	mids[2];
	t_range		range;
	int			turn;
	t_op		op;
	t_ps_node	*head;
	t_ps_node	*tail;

	/* ft_printf("??\nInitial things\n"); */
	/* dump_stacks(a, b); */
	turn = 0;
	while (a->len > 2)
	{
		ft_dprintf(2, "splitting on turn {%d}\n", turn);
		(void)ps_find_mids(a, mids);
		ps_setranges(a, turn, mids);
		/* getchar(); */
		while (helper_end_split(a, mids))
		{
			ps_takefrom_best(a, b, ops);
			dump_stacks(a, b);
			if (a->len == 2)
				break ;
			/* getchar(); */
		}
		turn++;
	}
}

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

	walk = b->head;
	while (walk)
	{
		if (GET_PS_NODE(walk)->turn == turn
				&& GET_PS_NODE(walk)->range == RANGE_MID)
			return RANGE_MID;
		walk = walk->next;
	}
	return RANGE_LOW;
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
		if (GET_PS_NODE(walk)->turn == turn && GET_PS_NODE(walk)->range == range
				&& GET_PS_NODE(walk)->val >= max)
		{
			node = GET_PS_NODE(walk);
			max = node->val;
			index = i;
		}
		i++;
		walk = walk->next;
	}
	ft_dprintf(2, "index of the largest node (%{cyan_fg}%d%{reset}) "
			   "is: %{yellow_fg}%d%{reset}\n", index, node->val);
	/* getchar(); */
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
	t_range range;
	t_dlst walk;

	if (!a || !b)
		return ;
	is_up = true;
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
		// NOTE: here I shall take the biggest one of the biggest turn
		// and prioritize RANGE_MID over RANGE_SMALL


		// get the target node and its index:
		int node_index = ps_find_largest_node(b);

		if (node_index == -1)
		{
			ft_dprintf(2, "NODE INDEX SHOULD NOT BE NEGATIVE! ABORT!");
			/* getchar(); */
			exit(0);
		}

		if (!b->len || (is_up = (node_index <= (int)b->len / 2)))
			rotate_count = node_index;
		else
			rotate_count = (int)b->len % node_index;

		ft_dprintf(2, "node index %d \n half b->len %d \n rotation count %d\n",
				   node_index, (int)b->len / 2, rotate_count);
		/* getchar(); */

		ft_dprintf(2, " >> rotate_count %d and rotation is %s\n",
					rotate_count, is_up ? "normal" : "reversed");
		/* getchar(); */
		/* walk = b->head; */
		while (rotate_count--)
		{
			op_dorot(b, is_up);
			op = OP_INIT(is_up ? OP_ROT : OP_RROT, APPLY_ON_B);
			ft_lstpush(ops, ft_lstnew(&op, sizeof(t_op)));
		}
		/* getchar(); */
		/* if (head->val < tail->val) */
		/* { */
		/* 	op_dorot(b, false); */
		/* 	op = OP_INIT(OP_RROT, APPLY_ON_B); */
		/* 	ft_lstpush(ops, ft_lstnew(&op, sizeof(t_op))); */
		/* 	ft_dprintf(2, "rotating stack B!!\n"); */
		/* 	dump_stacks(a, b); */
		/* 	getchar(); */
		/* } */

		op_dopsh(a, b);
		op = OP_INIT(OP_PUSH, APPLY_ON_A);
		ft_lstpush(ops, ft_lstnew(&op, sizeof(t_op)));
		dump_stacks(a, b);
		ft_dprintf(2, "after pushing\n");
		/* getchar(); */
		/* break; */
	}
}
