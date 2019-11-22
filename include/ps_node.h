/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_node.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 15:32:41 by archid-           #+#    #+#             */
/*   Updated: 2019/11/22 20:51:52 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_NODE_H
# define PS_NODE_H

# include "libft.h"

# define GET_NODE(e)					((t_ps_node *)e->content)

# define CHECK_MAX(val)					((long)val <= (long)INT_MAX)
# define CHECK_MIN(val)					((long)val >= (long)INT_MIN)
# define VALID_INT(val)					(CHECK_MAX(val) || CHECK_MIN(val))

typedef enum	e_comparison_operator
{
	/*
	** equal: ==  //  not_equal: !=
	*/
	CMP_EQ, CMP_NEQ,
	/*
	** less_or_equal <= // great_or_equal >=
	*/
	CMP_LE, CMP_GE,
	/*
	** less than <  //  greater than >
	*/
	CMP_LT, CMP_GT, CMP_OP_SIZE
}				t_cmp;

typedef struct	s_ps_node
{
	int		value;

	int		a_cost;
	int		b_cost;
}				t_ps_node;

void			ps_node_dump(t_lst e);
bool			ps_node_cmp(t_ps_node *u, t_ps_node *v, t_cmp cmp_op);

long			helper_get_val(char *str);

#endif
