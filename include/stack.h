/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 04:49:54 by archid-           #+#    #+#             */
/*   Updated: 2019/10/03 22:43:34 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include "libft.h"

# define ERROR_POP				(~0UL)

typedef t_s64	t_val;
typedef struct	s_push_swap_stack
{
	t_val	*stack;
	t_val	*tail;
	t_val	*mark;
	/*  */
}				*t_ps;

/* FIXME: erros must be handled using an error library */

/* FIXME: this should be in src/game/setup.c */
/* void			ps_init(t_ps *stack_a, t_ps *stack_b, int ac, char **av); */

/* main stack functions */
t_ps		ps_alloc(size_t size);
void		ps_del(t_ps *aps);
void		ps_dump(t_ps ps);

/* basic stack opeations */
void		ps_push(t_ps ps, t_val e);
t_val		ps_pop(t_ps ps);
bool		ps_isempty(t_ps ps);

#endif