/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 20:23:40 by archid-           #+#    #+#             */
/*   Updated: 2019/12/05 17:42:47 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

void		take_best_ops(t_lst *opt, t_lst *tmp,
							t_ps_node **anode, t_ps_node *current)
{
	if (*opt == NULL)
	{
		*opt = *tmp;
		*anode = current;
	}
	else if (ft_lstlen(*tmp) < ft_lstlen(*opt))
	{
		ft_lstdel(opt, lstdel_helper);
		*opt = *tmp;
		*anode = current;
	}
	else
		ft_lstdel(tmp, lstdel_helper);
}
