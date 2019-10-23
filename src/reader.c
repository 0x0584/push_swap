/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 21:36:42 by archid-           #+#    #+#             */
/*   Updated: 2019/10/23 04:09:14 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

t_ps	read_args(int ac, char**av)
{
	t_ps_node	node;
	t_ps		stack;
	long		val;
	int			i;

	i = 1;
	stack = ps_alloc('A', (size_t)ac);
	/* XXX: if any values is not a proper `int', we should
	   stop, free everything and return NULL */
	while (i < ac)
	{
		val = ft_atoll(av[i]);
		if (val > INT_VALMAX || val < INT_VALMIN)
		{
			ps_del(&stack);
			ft_putendl_fd("Fatal! in read_args: value is not a proper int", 2);
			break ;
		}
		node = (t_ps_node){.ord = stack->size - i++, .val = (int)val};
		ft_dlstpush(&stack->head->next, ft_dlstnew(&node, sizeof(t_ps_node)));
	}
	return (stack);
}

t_list			*read_input(void)
{
	char	buff[BUFF_SIZE + 1];
	ssize_t	ret;
	t_lst	ops;
	bool	flag;
	t_op	op;

	ops = NULL;
	flag = true;
	while (flag && (ret = read(0, buff, BUFF_SIZE)))
	{
		buff[ret] = '\0';
		if ((flag = op_isvalid(buff, &op) && ret > 0))
			ft_lstpush(&ops, ft_lstnew(&op, sizeof(t_op)));
	}
	if (!flag)
	{
		ft_lstdel(&ops, lstdel_helper);
		ft_putendl_fd("Fatal! in read_input: not a valid operator", 2);
	}
	return (ops);
}
