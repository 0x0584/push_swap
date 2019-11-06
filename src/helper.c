/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:16:42 by archid-           #+#    #+#             */
/*   Updated: 2019/11/06 13:31:42 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "ft_printf.h"

bool	helper_end_split(t_ps a)
{
	t_dlst	walk;
	bool	flag;

	flag = false;
	walk = a->head;
	while (walk)
	{
		if ((flag = GET_PS_NODE(walk)->range == RANGE_LOW))
			break ;
		walk = walk->next;
	}
	return (flag);
}

void	helper_node_dump(t_dlst e)
{
	/* static int i = 0; */

	if (!e)
		return ;
	/* TODO: update repo's libft */
	if (GET_PS_NODE(e)->range == RANGE_LOW)
		ft_dprintf(2, "%{green_fg}%4d(%d)%{reset} ",
				  GET_PS_NODE(e)->val, GET_PS_NODE(e)->turn);
	else if (GET_PS_NODE(e)->range == RANGE_HIGH)
		ft_dprintf(2, "%{red_fg}%4d(%d)%{reset} ",
				  GET_PS_NODE(e)->val, GET_PS_NODE(e)->turn);

	/* if (i++ && i % 5 == 0) */
	/* 	ft_putendl_fd("\n", 2); */
	/* ft_printf("(%p | ord: %d, val: %d, turn: %d)\n", e,
		GET_PS_NODE(e)->ord, */
	/* 			GET_PS_NODE(e)->val, GET_PS_NODE(e)->turn); */
}

void	ps_fdump(t_ps ps)
{
	int i;
	t_dlst walk;
	char *s;

	i = 0;

	walk = ps->head;
	while (walk)
	{
		if (GET_PS_NODE(walk)->range == RANGE_LOW)
			ft_dprintf(2, "%{green_fg}%4d(%d)%{reset} ",
					   GET_PS_NODE(walk)->val, GET_PS_NODE(walk)->turn);
		else if (GET_PS_NODE(walk)->range == RANGE_HIGH)
			ft_dprintf(2, "%{red_fg}%4d(%d)%{reset} ",
					   GET_PS_NODE(walk)->val, GET_PS_NODE(walk)->turn);

		if (i++ && i % 5 == 0) ft_dprintf(2, "\n");

		walk = walk->next;
	}
}

void	dump_stacks(t_ps a, t_ps b)
{
	t_dlst walk;
	int i;

	ft_dprintf(2, "////\n");
	ft_dprintf(2, " A:[\n");

	i = 0;
	ps_fdump(a);
	/* ft_dlstiter(a->head, helper_node_dump); */
	ft_dprintf(2, "\n]\n B:[\n");
	ps_fdump(b);
	ft_dprintf(2, "\n]\n////\n");
}
