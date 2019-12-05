/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 21:36:42 by archid-           #+#    #+#             */
/*   Updated: 2019/12/05 14:26:59 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static bool	check_node(t_ps ps, t_ps_node *node)
{
	t_lst		walk;

	walk = ps->stack;
	while (walk && (AS_NODE(walk->content)->value != node->value))
		walk = walk->next;
	return (walk == NULL);
}

static long	get_numeric_val(char *str)
{
	size_t		i;
	long		val;

	if (!SAFE_PTRVAL(str))
		return (LONG_MIN);
	i = (ft_strchr("+-", *str) ? 1 : 0);
	if (ft_strlen(str + i) > 10)
		return (LONG_MIN);
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (LONG_MIN);
	}
	val = ft_atol(str);
	return (val >= INT_MIN && val <= INT_MAX ? val : LONG_MIN);
}

int			parse_flags(int ac, char **av, t_flags *flags)
{
	int i;
	int j;

	if (!flags)
		return (1);
	i = 1;
	ft_bzero(flags, sizeof(t_flags));
	flags->fd_out = 1;
	while (i < ac)
	{
		j = 0;
		if (av[i][j] != '-' || ft_isdigit(av[i][j + 1]))
			break ;
		while (av[i][j++])
		{
			if (flags->fd_out == 1 && av[i][j] == FLAG_OUT)
				flags->fd_out = open(FLAG_OUT_FILE, O_RDWR | O_CREAT, 0644);
			if (!flags->verbose && av[i][j] == FLAG_VERBOSE)
				flags->verbose = true;
			if (!flags->color && av[i][j] == FLAG_COLOR)
				flags->color = true;
		}
		i++;
	}
	return (i);
}

t_ps		read_args(int ac, char **av, t_flags *flags)
{
	t_ps_node	node;
	t_ps		ps;
	long		val;
	int			i;

	if (ac < 2 || !SAFE_PTRVAL(av))
		return (NULL);
	i = parse_flags(ac, av, flags);
	ps = ps_alloc('A', (size_t)(ac - i));
	ps->len = ac - i;
	while (i < ac)
	{
		val = get_numeric_val(av[i++]);
		node = (t_ps_node){(int)val, 0, 0};
		if (val == LONG_MIN || !check_node(ps, &node))
		{
			ft_putendl_fd("ERROR", 2);
			ps_del(&ps);
			break ;
		}
		ft_lstpush(&ps->stack, ft_lstnew(&node, sizeof(t_ps_node)));
	}
	return (ps);
}

bool		read_input(t_lst *ops)
{
	char		*buff;
	t_op		op;
	bool		flag;

	flag = true;
	while (flag && gnl(0, &buff) > 0)
	{
		flag = ft_strlen(buff) <= 3;
		ft_striter(buff, striter_tolower);
		op = OP_INIT(OP_NA, APPLY_NA);
		if (flag && (flag = op_isvalid(buff, &op)))
			ft_lstpush(ops, ft_lstnew(&op, sizeof(t_op)));
	}
	ft_strdel(&buff);
	if (!flag)
	{
		ft_lstdel(ops, lstdel_helper);
		ft_putendl_fd("ERROR", 2);
	}
	return (flag);
}
