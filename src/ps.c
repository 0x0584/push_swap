/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:22:14 by archid-           #+#    #+#             */
/*   Updated: 2019/11/02 15:22:52 by archid-          ###   ########.fr       */
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
	printf("stack: %c[%zu/%zu]\n------------------\n",
			ps->symb, ps->len, ps->size);
	walk = ps->head;
	while (walk)
	{
		node = (t_ps_node *)walk->blob;
		printf("{%p/%d: %d}\n", walk, node->ord, node->val);
		walk = walk->next;
	}
	printf("------------------\n");
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

	if (!ps_a || !ps_b || !ps_a->head || ps_b->head)
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

static t_dlst		helper_merge(t_dlst left, t_dlst right,
									int (cmp)(t_dlst, t_dlst))
{
	t_dlst root;
	bool	sort_on_left;

	if (!left || !right)
		return (!left ? right : left);
	sort_on_left = cmp(left, right) > 0;
	root = sort_on_left ? left : right;
	root->next = helper_merge(sort_on_left ? left->next : left,
								sort_on_left ? right : right->next,
								cmp);
	return (root);
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

void		helper_node_dump(t_dlst e)
{
	if (!e)
		return ;
	/* TODO: update repo's libft */
	printf("(%p| ord: %d, val: %d)\n", e, GET_PS_NODE(e)->ord,
		   GET_PS_NODE(e)->val);
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
	walk = sorted_a->head;
	while (walk)
	{
		i = 0;
		while (i++ < ONE_THIRD(a->size))
			walk = walk->next;
		mids[index] = *GET_PS_NODE(walk);
		if (index++)
			walk = NULL;
	}
	ps_del(&sorted_a);
}

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

void	dump_stacks(t_ps a, t_ps b)
{
	ft_printf("////\n");
	ft_printf(" This Stack A:\n");
	ft_dlstiter(a->head, helper_node_dump);
	ft_printf(" This Stack B:\n");
	ft_dlstiter(b->head, helper_node_dump);
	ft_printf("////\n");
}

void	ps_split_ranges(t_ps a, t_ps b)
{
	t_ps_node	mids[2];
	t_range		range;

	ft_printf("??\n");
	ps_find_mids(a, mids);

	ft_printf(" ]]] val: %d ord: %d\n", mids[0].val, mids[0].ord);
	ft_printf(" ]]] val: %d ord: %d\n", mids[1].val, mids[1].ord);
	getchar();
	ft_printf("Initial things\n");
	dump_stacks(a, b);
	/* NOTE: set turn in place */
	while (helper_end_split(a, mids))
	{
		range = ps_whichrange(a, mids);
		ft_printf("val: %d is in range %d\n",
					GET_PS_NODE(a->head)->val, range);
		if (range == RANGE_LOW)
			op_dorot(b, true);
		if (range < RANGE_HIGH)
			op_dopsh(b, a);
		if (range != RANGE_LOW && range != RANGE_MID)
			op_dorot(a, true);
		dump_stacks(a, b);
		getchar();
	}
}
