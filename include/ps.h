/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:10:29 by archid-           #+#    #+#             */
/*   Updated: 2019/11/14 16:37:02 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_H
# define PS_H

# include "dlst.h"

# define DEBUG_SPLIT					1
# define DEBUG_REFILL					1

# define ONE_THIRD(foo)					((foo) / 3)
# define GET_PS_NODE(dlst)				((t_ps_node *)dlst->blob)

# define RANGE_LOW_SPLIT_SIZE			5
# define RANGE_HIGH_SPLIT_SIZE			11

typedef int		t_val;

typedef enum	e_ranges
{
	RANGE_NA,

	RANGE_LOW = RANGE_LOW_SPLIT_SIZE,
	RANGE_HIGH = RANGE_HIGH_SPLIT_SIZE
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
	t_ps_node *mid;
}				*t_ps;

t_ps		ps_alloc(char symb, size_t size);
void		ps_del(t_ps *aps);
void		ps_dump(t_ps ps);
bool		ps_issorted(t_ps ps_a, t_ps ps_b);
t_ps		ps_mergesort(t_ps ps);
t_ps		ps_clone(t_ps const ps);
void		helper_node_dump(t_dlst e);
void		ps_split_ranges(t_ps a, t_ps b, t_lst *ops);
t_range		ps_whichrange(t_val val, t_ps_node *mid);
t_ps_node 	*ps_find_mids(t_ps sorted_a);
void		ps_refill(t_ps a, t_ps b, t_lst *ops);
void		ps_sort_remainder(t_ps a, t_lst *ops);

void		helper_node_dump(t_dlst e);
void		dump_stacks(t_ps a, t_ps b);

void		ps_split_ranges(t_ps a, t_ps b, t_lst *ops);
void		ps_refill(t_ps a, t_ps b, t_lst *ops);

t_range		ps_find_ranges(t_ps a);

bool		split_end(t_ps a, int prev_turn);

#endif
