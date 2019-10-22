/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:10:29 by archid-           #+#    #+#             */
/*   Updated: 2019/10/22 03:53:18 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_H
# define PS_H

# include "libft.h"

typedef struct s_ps_node
{
	int ord;
	int val;
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

	t_lst	head;
	t_lst	tail;

	size_t	len;
	size_t	size;
}				*t_ps;

t_ps	ps_alloc(char symb, size_t size);
void	ps_free(t_ps *aps);

void	ps_node_free(void *content, size_t content_size);

#endif /* PS_H */
