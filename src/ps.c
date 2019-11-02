/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:22:14 by archid-           #+#    #+#             */
/*   Updated: 2019/11/02 09:30:30 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

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

static void			helper_halfsplit(t_dlst root, t_dlst *ahead,
										t_dlst *atail)
{
	t_dlst foo;
	t_dlst bar;

	bar = root;
	foo = root->next;
	while (foo)
	{
		foo = foo->next;
		if (foo)
		{
			bar = bar->next;
			foo = foo->next;
		}
	}
	*ahead = root;
	*atail = bar->next;
	bar->next = NULL;
}

static void		helper_fix_prev(t_dlst lst)
{
	t_dlst prev;

	if (lst == NULL)
		return ;
	lst->prev = NULL;
	prev = NULL;
	while (lst)
	{
		lst->prev = prev;
		prev = lst;
		lst = lst->next;
	}
}

void				ft_dlstmergesort(t_dlst *alst, int (cmp)(t_dlst, t_dlst))
{
	t_dlst left;
	t_dlst right;

	if (!alst || !*alst || !(*alst)->next)
		return ;
	helper_halfsplit(*alst, &left, &right);
	ft_dlstmergesort(&left, cmp);
	ft_dlstmergesort(&right, cmp);
	helper_fix_prev(*alst = helper_merge(left, right, cmp));
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
