/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 21:36:42 by archid-           #+#    #+#             */
/*   Updated: 2019/11/22 21:13:48 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

/* FIXME: check duplicates */

t_ps	read_args(int ac, char**av)
{
	t_ps_node	node;
	t_ps		ps;
	long		val;
	int			i;

	if (ac < 2 || !SAFE_PTRVAL(av))
		return (NULL);
	i = 1;
	ps = ps_alloc('a', (size_t)(ac - 1));
	ps->len = ac;
	while (i < ac)
	{
		val = ft_atol(av[i++]);
		node = (t_ps_node){(int)val, 0, 0};
		if (!VALID_INT(val) || !ps_check_node(ps, &node))
		{
			ps_del(&ps);
#if DEBUG_READ
			ft_dprintf(2, "%{RED_fg}Fatal!%{reset} in read_args: "
					   "%{yellow_fg}value (%s) is not a proper int%{reset}",
					   av[i]);
#endif
			break ;
		}
		ft_lstpush(&ps->stack, ft_lstnew(&node, sizeof(t_ps_node)));
		if (ps->max.value < val)
			ps->max.value = val;
		if (ps->min.value > val)
			ps->min.value = val;
	}
	return (ps);
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
