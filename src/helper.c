/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:16:42 by archid-           #+#    #+#             */
/*   Updated: 2019/11/14 17:25:39 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "ft_printf.h"

#define ROW_SIZE					5

void	helper_op_dump(t_lst e)
{
	t_op *op;

	op = e->content;
	op_dump(*op);
}

void	helper_op_free(void *content, size_t size)
{
	if (size)
		free(content);
}

void	helper_node_dump(t_dlst e)
{
	t_ps_node *node;

	if (!e || !(node = GET_PS_NODE(e)))
		return ;
	ft_dprintf(2, "%{green_fg}(%.3d)%{yellow_fg}%+.3d%{blue_fg}[%.3d]%{reset} ",
				node->turn, node->val, node->ord);
}

void	helper_fdump(t_ps ps)
{
	int i;
	t_dlst walk;

	i = 0;

	walk = ps->head;
	while (walk)
	{
		helper_node_dump(walk);
		ft_dprintf(2, "%s", (i++ && i % ROW_SIZE == 0) ? "\n" : "");
		walk = walk->next;
	}
}

void	dump_stacks(t_ps a, t_ps b)
{
	ft_dprintf(2, "////\n");
	ft_dprintf(2, " %c:[\n", a->symb);
	helper_fdump(a);
	ft_dprintf(2, "\n]\n %c:[\n", b->symb);
	helper_fdump(b);
	ft_dprintf(2, "\n]\n////\n");
}
