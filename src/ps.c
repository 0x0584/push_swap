/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:22:14 by archid-           #+#    #+#             */
/*   Updated: 2019/11/09 19:47:03 by archid-          ###   ########.fr       */
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

t_range		ps_whichrange(t_val val, t_ps_node *mid)
{
	/* TODO: check whether mid is included or excluded */
	if (val < mid->val)
		return (RANGE_LOW);
	return (RANGE_HIGH);
}

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
	ft_dprintf(2, "mid is %d\n", mid->val);
	ps_del(&sorted_a);
	return mid;
}

/*
   this shall always pick the best way to get a node.
   ie, based on the distribution of the numbers, find
   the best way to pick them. That's the key to the highway!
*/

void	ps_takefrom_best(t_ps a, t_ps b, t_lst *ops)
{
	t_ps_node	*head;
	t_ps_node	*tail;
	t_op		op;
	bool		is_up;

	head = GET_PS_NODE(a->head);
	tail = GET_PS_NODE(ft_dlst_gettail(a->head));
	ft_dprintf(2, "Current node"); helper_node_dump(a->head);
	ft_dprintf(2, "\n");
	if (head->range == RANGE_LOW)
	{
		op_dopsh(b, a);
		op = OP_INIT(OP_PUSH, APPLY_ON_B);
		ft_lstpush(ops, ft_lstnew(&op, sizeof(t_op)));
	}
	else if (head->range == RANGE_HIGH)
	{
		is_up = (tail->range == RANGE_HIGH);
		/* is_up = true; */
		op_dorot(a, is_up);
		op = OP_INIT(is_up ? OP_ROT : OP_RROT, APPLY_ON_A);
		ft_lstpush(ops, ft_lstnew(&op, sizeof(t_op)));
	}
}

void	ps_setranges(t_ps a, int turn)
{
	t_dlst walk;

	a->mid = ps_find_mids(a);
	walk = a->head;
	while (walk)
	{
		GET_PS_NODE(walk)->turn = turn;
		GET_PS_NODE(walk)->range =
			ps_whichrange(GET_PS_NODE(walk)->val, a->mid);
		walk = walk->next;
	}
}

void	ps_split_ranges(t_ps a, t_ps b, t_lst *ops)
{
	int	turn;

	turn = 0;
	while (a->len > 2)
	{
		ft_dprintf(2, "splitting on turn {%d}\n", turn);
		ps_setranges(a, turn);
		ft_dprintf(2, "this is the current mid %d", a->mid->val);
		/* getchar(); */
		while (helper_end_split(a))
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
				&& GET_PS_NODE(walk)->range == RANGE_LOW)
			return RANGE_LOW;
		walk = walk->next;
	}
	return RANGE_HIGH;
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
		if (GET_PS_NODE(walk)->turn == turn
				&& GET_PS_NODE(walk)->range == range
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
}
