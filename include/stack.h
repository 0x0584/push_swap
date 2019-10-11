/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 04:49:54 by archid-           #+#    #+#             */
/*   Updated: 2019/10/11 05:15:43 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include "libft.h"

/* FIXME: all ps_* functions should return status values */
# define ERROR_POP				(~0L)

# define PS_ISEMPTY(ps)			(ps->mark == ps->tail)
# define PS_ISFULL(ps)			(ps->mark == ps->head)

/* FIXME: this should be protected and checked */
# define PS_LENGTH(ps)			(ps->tail - ps->mark)
# define PS_SIZE(ps)			(ps->tail - ps->head + 1)

typedef t_s32	t_val;
typedef struct	s_push_swap_stack
{
	char	label;				/* to distinguish stacks when logging */

	t_val	*head;				/* the head of the  */
	t_val	*tail;				/* its tail */
	t_val	*mark;				/* always off-by-one */
}				*t_ps;

/* FIXME: erros must be handled using an error library */

/* FIXME: this should be in src/game/setup.c */
/* void			ps_init(t_ps *stack_a, t_ps *stack_b, int ac, char **av); */

/* main stack functions */
t_ps		ps_alloc(char label, size_t size);
void		ps_del(t_ps *aps);
void		ps_dump(t_ps ps);
bool		ps_issorted(t_ps ps);

/* basic stack opeations */
void		ps_push(t_ps ps, t_val e);
t_val		ps_pop(t_ps ps);

/* push_swap's operations */
/* FIXME: add a return status */
void		ps_psh(t_ps dest, t_ps src);
void		ps_swp(t_ps stack);
void		ps_rot(t_ps stack, bool isup);

#endif
