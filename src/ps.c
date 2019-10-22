/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:22:14 by archid-           #+#    #+#             */
/*   Updated: 2019/10/22 03:53:55 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

t_ps	ps_alloc(char symb, size_t size)
{
	t_ps ps;

	if (!(ps = ALLOC(t_ps, 1, sizeof(struct s_ps_ds))))
		return (NULL);
	ps->head = ft_lstnew(NULL, 0);
	ps->tail = ft_lstnew(NULL, 0);
	ps->symb = symb;
	ps->size = size;
	return (ps);
}

void	ps_free(t_ps *aps)
{
	if (!SAFE_PTRVAL(aps))
		return ;
	ft_lstdel(&(*aps)->nodes, lstdel_helper);
	free(*aps);
	*aps = NULL;
}
