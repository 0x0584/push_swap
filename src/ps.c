/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:22:14 by archid-           #+#    #+#             */
/*   Updated: 2019/10/23 04:10:26 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void	ps_dump(t_ps ps)
{
	t_dlst		walk;
	t_ps_node	*node;

	if (!ps)
		return ;
	printf("stack: %c[%zu/%zu]\n(head: %p, tail: %p)\n------------------\n",
			ps->symb, ps->len, ps->size, ps->head, ps->tail);
	walk = ps->tail->prev;
	while (walk->prev)
	{
		node = (t_ps_node *)walk->blob;
		printf("{%p/%d: %d}\n", walk, node->ord, node->val);
		walk = walk->prev;
	}
	printf("------------------\n");
}

t_ps	ps_alloc(char symb, size_t size)
{
	t_ps ps;

	if (!(ps = ALLOC(t_ps, 1, sizeof(struct s_ps_ds))))
		return (NULL);
	ps->head = ft_dlstnew(NULL, 0);
	ps->tail = ft_dlstpush(&ps->head, ft_dlstnew(NULL, 0));
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
