/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_node.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 15:32:15 by archid-           #+#    #+#             */
/*   Updated: 2019/11/19 16:54:33 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_node.h"

bool	ps_node_cmp(t_ps_node *u, t_ps_node *v, t_cmp cmp_op)
{
	if (!u || !v)
		return (false);
	if (cmp_op == CMP_EQ)
		return (u->value == v->value);
	else if (cmp_op == CMP_NEQ)
		return (u->value != v->value);
	else if (cmp_op == CMP_LE)
		return (u->value <= v->value);
	else if (cmp_op == CMP_GE)
		return (u->value >= v->value);
	else if (cmp_op == CMP_LT)
		return (u->value < v->value);
	else if (cmp_op == CMP_GT)
		return (u->value > v->value);
	return (false);
}
