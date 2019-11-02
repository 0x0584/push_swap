/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:10:29 by archid-           #+#    #+#             */
/*   Updated: 2019/11/02 13:54:10 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_H
# define PS_H

# include "dlst.h"

# define ONE_THIRD(foo)					((foo) / 3)
# define GET_PS_NODE(dlst)				((t_ps_node *)dlst->blob)

typedef int		t_val;
typedef enum	e_ranges
{
	RANGE_LOW, RANGE_MID,
	RANGE_HIGH, RANGE_NA
}				t_range;



typedef struct	s_ps_node
{
	/*
	   NOTE: holding the order for each node so that if we
	   reverse, we can set the node to it's initial place
	*/
	int		turn;
	t_val	ord;
	t_val	val;
}				t_ps_node;

/*
   NOTE: About push_swap data structre
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

   if the stack, ps, is empty, then ps->nodes is NULL.
   the head always contains the first entry, tail points on the last one.
   using a head and tail to reduce complexity of the `push_swap' operations.
*/

typedef struct s_ps_ds
{
	char	symb;

	t_dlst	head;
	t_dlst	tail;

	size_t	len;
	size_t	size;
}				*t_ps;

t_ps		ps_alloc(char symb, size_t size);
void		ps_del(t_ps *aps);
void		ps_dump(t_ps ps);
bool		ps_issorted(t_ps ps_a, t_ps ps_b);
t_ps		ps_mergesort(t_ps ps);
t_ps		ps_clone(t_ps const ps);
void		helper_node_dump(t_dlst e);
t_range		ps_whichrange(t_ps a, t_ps_node *mids);
void		ps_split_ranges(t_ps a, t_ps b);
void		ps_find_mids(t_ps sorted_a, t_ps_node *mids);

#endif
