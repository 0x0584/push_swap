/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:10:29 by archid-           #+#    #+#             */
/*   Updated: 2019/11/15 18:12:33 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_H
# define PS_H

# include "libft.h"

# define GET_NODE(e)						((t_ps_node *)e->content)

typedef struct	s_ps_node
{
	int value;
	int count;
}				t_ps_node;

typedef struct	s_ps_ds
{
	char	symb;
	t_lst	stack;
	size_t	len;
	size_t	size;
}				*t_ps;

t_ps		ps_alloc(char symb, size_t size);
void		ps_del(t_ps *aps);
void		ps_dump(t_ps ps);
bool		ps_issorted(t_ps ps_a, t_ps ps_b);
void		helper_node_dump(t_lst e);
void		dump_stacks(t_ps a, t_ps b);

#endif
