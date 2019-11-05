/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 21:36:42 by archid-           #+#    #+#             */
/*   Updated: 2019/11/04 20:42:48 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

t_ps	read_args(int ac, char**av)
{
	t_ps_node	node;
	t_ps		stack;
	long		val;
	int			i;

	if (ac < 2 || !SAFE_PTRVAL(av))
		return (NULL);
	i = 0;
	stack = ps_alloc('A', (size_t)--ac);
	stack->len = ac;
	while (i < ac)
	{
		val = ft_atoll(av[i + 1]);
		if (val > (long)INT_MAX || val < (long)INT_MIN)
		{
			ps_del(&stack);
			ft_putendl_fd("Fatal! in read_args: value is not a proper int", 2);
			break ;
		}
		node = (t_ps_node){.ord = ac - i++, .val = (int)val};
		ft_dlstpush(&stack->head, ft_dlstnew(&node, sizeof(t_ps_node)));
	}
	stack->tail = ft_dlst_gettail(stack->head);
	return (stack);
}

void	striter_tolower(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
	{
		s[i] = ft_tolower(s[i]);
		i++;
	}
}

t_lst	read_input(void)
{
	char	*buff;
	t_lst	ops;
	t_op	op;
	bool	flag;

	ops = NULL;
	flag = true;
	while (flag && gnl(0, &buff))
	{
		ft_striter(buff, striter_tolower);
		op = OP_INIT(OP_NA, APPLY_NA);
		if ((flag = op_isvalid(buff, &op)))
			ft_lstpush(&ops, ft_lstnew(&op, sizeof(t_op)));
		op_dump(op);
		ft_strdel(&buff);
	}
	if (!flag)
	{
		ft_lstdel(&ops, lstdel_helper);
		ft_putendl_fd("Fatal! in read_input: not a valid operator", 2);
	}
	return (ops);
}
