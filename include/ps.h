/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:10:29 by archid-           #+#    #+#             */
/*   Updated: 2019/11/25 04:33:01 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_H
# define PS_H
# define FEW_ELEMENTS							(3)

# include "ps_node.h"

typedef struct	s_ps_array
{
	int		*base;
	size_t	size;
}				t_ps_array;

typedef struct	s_ps_ds
{
	char	symb;
	t_lst	stack;
	size_t	len;
	size_t	size;

	t_ps_node max;
	t_ps_node min;
}				*t_ps;

t_ps		ps_alloc(char symb, size_t size);
void		ps_del(t_ps *aps);
void		ps_dump(t_ps ps);
bool		ps_issorted(t_ps ps_a, t_ps ps_b);
t_ps_array	ps_vals_asarray(t_ps ps);
void		ps_sort_few(t_ps a, t_ps b, t_lst *ops);
bool		ps_check_node(t_ps ps, t_ps_node *node);
void		helper_node_dump(t_lst e);

void		dump_stacks(t_ps ps_a, t_ps ps_b);

#endif
