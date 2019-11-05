/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:16:42 by archid-           #+#    #+#             */
/*   Updated: 2019/11/05 15:58:26 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "ft_printf.h"

void	helper_node_dump(t_dlst e)
{
	if (!e)
		return ;
	/* TODO: update repo's libft */
	if (GET_PS_NODE(e)->range == RANGE_LOW)
		ft_dprintf(2, "%{green_fg}%d(%d)%{reset} ",
				  GET_PS_NODE(e)->val, GET_PS_NODE(e)->turn);
	else if (GET_PS_NODE(e)->range == RANGE_MID)
		ft_dprintf(2, "%{blue_fg}%d(%d)%{reset} ",
				  GET_PS_NODE(e)->val, GET_PS_NODE(e)->turn);
	else if (GET_PS_NODE(e)->range == RANGE_HIGH)
		ft_dprintf(2, "%{red_fg}%d(%d)%{reset} ",
				  GET_PS_NODE(e)->val, GET_PS_NODE(e)->turn);

	/* ft_printf("(%p | ord: %d, val: %d, turn: %d)\n", e,
		GET_PS_NODE(e)->ord, */
	/* 			GET_PS_NODE(e)->val, GET_PS_NODE(e)->turn); */
}

void	dump_stacks(t_ps a, t_ps b)
{
	ft_dprintf(2, "////\n");
	ft_dprintf(2, " A:[");
	ft_dlstiter(a->head, helper_node_dump);
	ft_dprintf(2, "]\n B:[");
	ft_dlstiter(b->head, helper_node_dump);
	ft_dprintf(2, "]\n////\n");
}
