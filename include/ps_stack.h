/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_stack.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 04:49:54 by archid-           #+#    #+#             */
/*   Updated: 2019/10/03 05:34:46 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include "libft.h"

typedef struct s_push_swap_stack
{
	t_s64			*stack;
	t_s64			*head;
	t_u32			size;
}				*t_ps;

// FIXME: this should be in src/game/setup.c
// void			ps_init(t_ps *stack_a, t_ps *stack_b, int ac, char **av);

t_ps		ps_alloc(size_t size);

#endif
