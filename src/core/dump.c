/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:17:31 by archid-           #+#    #+#             */
/*   Updated: 2019/12/05 16:33:45 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include "dump.h"
#include "op.h"

void	op_dump_fd(t_op op, int fd)
{
	char *prefix;
	char *suffix;

	prefix = "psrr";
	suffix = "ab";
	ft_dprintf(fd, "%c", prefix[op.op]);
	if (op.op == OP_RROT)
		ft_dprintf(fd, "%c", 'r');
	if (op.which != APPLY_ON_BOTH)
		ft_dprintf(fd, "%c", suffix[op.which]);
	else if (op.op == OP_ROT || op.op == OP_RROT)
		ft_dprintf(fd, "%c", 'r');
	else
		ft_dprintf(fd, "%c", 's');
	ft_dprintf(fd, "\n");
}

void	dump_ops(t_lst ops, t_flags *flags)
{
	t_lst walk;

	walk = ops;
	while (walk)
	{
		op_dump_fd(*(t_op *)walk->content, flags->fd_out);
		walk = walk->next;
	}
}

void	ps_dump(t_ps ps)
{
	t_qnode		*walk;
	t_ps_node	*node;
	int			i;

	if (!ps)
		return ;
	i = 0;
	walk = ps->stack->head->next;
	ft_dprintf(2, "\n   stack: %c[%zu/%zu]\n\n",
				ps->symb, ps->len, ps->size);
	while (walk != ps->stack->tail)
	{
		node = walk->blob;
		ft_dprintf(2, "   %{green_fg}%+4d%{yellow_fg}"
					"[%+.2d]%{blue_fg}[%+.2d]%{reset}\n",
					node->value, node->a_cost, node->b_cost);
		i++;
		walk = walk->next;
	}
}

void	dump_stacks(t_ps a, t_ps b)
{
	ps_dump(a);
	ft_putchar_fd('\n', 2);
	ps_dump(b);
	ft_putchar_fd('\n', 2);
}

void	dump_state(t_ps a, t_ps b, t_lst ops, t_ps_node *node)
{
	static int	i = 0;
	t_lst		walk;
	char		c;

	ft_dprintf(2, "\e[1;1H\e[2J");
	dump_stacks(a, b);
	if (node)
		ft_dprintf(2, "\e[2;30Htarget node: %{green_fg}%+4d%{yellow_fg}"
					"[%+.2d]%{blue_fg}[%+.2d]%{reset}\n",
					node->value, node->a_cost, node->b_cost);
	if ((walk = ops))
		ft_dprintf(1, "\e[2E\e[30GOperations\n\n");
	while (walk)
	{
		i++;
		ft_dprintf(2, "\e[30G");
		op_dump_fd(*(t_op *)walk->content, 2);
		walk = walk->next;
	}
	if (ops)
		ft_dprintf(2, "\n\e[30GTotal: %d\e[1;1H", i);
	read(1, &c, 1);
}
