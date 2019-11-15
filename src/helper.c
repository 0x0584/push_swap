/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:16:42 by archid-           #+#    #+#             */
/*   Updated: 2019/11/15 18:13:01 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "ft_printf.h"

#define ROW_SIZE							10

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

void	helper_node_dump(t_lst e)
{
	t_ps_node *node;

	if (!e || !(node = GET_NODE(e)))
		return ;
	ft_dprintf(2, "%{green_fg}%+.3d%{blue_fg}(%.3d)%{reset} ",
				node->value, node->count);
}

void	helper_fdump(t_ps ps)
{
	int i;
	t_lst walk;

	i = 0;

	walk = ps->stack;
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


void	do_ops(t_ps a, t_ps b)
{
	char *s_op;
	t_op op;

	s_op = NULL;
	while (gnl(0, &s_op))
	{
		if (!op_isvalid(s_op, &op))
			break;
		op_apply(op, a, b);
		dump_stacks(a, b);
		free(s_op);
	}

}
