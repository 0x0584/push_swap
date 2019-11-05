/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:22:14 by archid-           #+#    #+#             */
/*   Updated: 2019/11/05 15:53:45 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"
#include "op.h"
#include "ft_printf.h"

bool	helper_end_split(t_ps a, t_ps_node *mids)
{
	t_dlst	walk;
	bool	flag;

	flag = false;
	walk = a->head;
	while (walk)
	{
		if ((flag = GET_PS_NODE(walk)->val < mids[1].val))
			break ;
		walk = walk->next;
	}
	return (flag);
}

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

t_range		ps_whichrange(t_ps a, t_ps_node *mids)
{
	if (!a)
		return (RANGE_NA);
	/* TODO: check whther mid is included or excluded */
	if (GET_PS_NODE(a->head)->val < mids[0].val)
		return (RANGE_LOW);
	else if (GET_PS_NODE(a->head)->val >= mids[0].val
				&& GET_PS_NODE(a->head)->val < mids[1].val)
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
		if (index++)
			walk = NULL;
	}
	ft_dprintf(2, "lower mid: %d higher mid: %d\n", mids[0].val, mids[1].val);
	/* getchar(); */
	ps_del(&sorted_a);
}

void	ps_split_ranges(t_ps a, t_ps b, t_lst *ops)
{
	t_ps_node	mids[2];
	t_range		range;
	int			turn;
	t_op		op;

	/* ft_printf("??\nInitial things\n"); */
	/* dump_stacks(a, b); */
	turn = 0;
	while (a->len > 2)
	{
		ft_dprintf(2, "splitting on turn {%d}\n", turn);
		ps_find_mids(a, mids);
		/* ft_printf("turn: %d\n ]]] val: %d ord: %d\n", turn, */
		/* 			mids[0].val, mids[0].ord); */
		/* ft_printf(" ]]] val: %d ord: %d\nnew turn!!", */
		/* 		  mids[1].val, mids[1].ord); */
		/* getchar(); */

		while (helper_end_split(a, mids))
		{
			range = ps_whichrange(a, mids);
			/* ft_printf("val: %d is in range %d\n", */
			/* 			GET_PS_NODE(a->head)->val, range); */
			GET_PS_NODE(a->head)->turn = turn;
			GET_PS_NODE(a->head)->range = range;
			if (range == RANGE_LOW || range == RANGE_MID)
			{
				op_dopsh(b, a);
				op = OP_INIT(OP_PUSH, APPLY_ON_B);
				ft_lstpush(ops, ft_lstnew(&op, sizeof(t_op)));
			}
			if (range == RANGE_LOW && b->len > 1)
			{
				op_dorot(b, true);
				op = OP_INIT(OP_ROT, APPLY_ON_B);
				ft_lstpush(ops, ft_lstnew(&op, sizeof(t_op)));
			}
			if (range == RANGE_HIGH)
			{
				op_dorot(a, true);
				op = OP_INIT(OP_ROT, APPLY_ON_A);
				ft_lstpush(ops, ft_lstnew(&op, sizeof(t_op)));
			}
			dump_stacks(a, b);
			/* getchar(); */

			/* if (ps_issorted(a, NULL)) */
			/* 	break ; */
		}
		/* dump_stacks(a, b); */
		/* getchar(); */
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
		op_doswp(a);
		op = OP_INIT(OP_SWAP, APPLY_ON_A);
		ft_lstpush(ops, ft_lstnew(&op, sizeof(t_op)));
	}
}

int		ps_whichturn(t_ps b)
{
	int turn = 0;
	t_dlst walk;

	return MAX(GET_PS_NODE(b->head)->turn, GET_PS_NODE(b->tail)->turn);
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
	while (b->len)
	{
		head = GET_PS_NODE(b->head);
		tail = GET_PS_NODE(ft_dlst_gettail(b->head));
		/* tail = GET_PS_NODE(b->tail); */
		ft_dprintf(2, "{%d} head: %d tail: %d\n", turn++, head->val, tail->val);
		if (head->val < tail->val)
		{
			op_dorot(b, false);
			op = OP_INIT(OP_RROT, APPLY_ON_B);
			ft_lstpush(ops, ft_lstnew(&op, sizeof(t_op)));
			ft_dprintf(2, "rotating stack B!!\n");
			dump_stacks(a, b);
			/* getchar(); */
		}

		op_dopsh(a, b);
		op = OP_INIT(OP_PUSH, APPLY_ON_A);
		ft_lstpush(ops, ft_lstnew(&op, sizeof(t_op)));
		dump_stacks(a, b);
		ft_dprintf(2, "after pushing\n");
		/* getchar(); */
		/* break; */
	}
}
