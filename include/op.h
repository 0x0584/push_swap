/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 04:57:57 by archid-           #+#    #+#             */
/*   Updated: 2019/10/11 05:07:12 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

#include "types.h"
#include "stack.h"

#define WHICH_HELPER(c)				(c == 'a' ? OP_TO_A : OP_TO_B)

enum	e_ops
{
	OP_PUSH, OP_SWAP, OP_REV,
	OP_RREV, OP_NIL,

	OP_TO_A = 0,
	OP_TO_B, OP_TO_BOTH
};

bool	is_op(const char *buffer);

bool	apply_push(t_ps foo, t_ps bar, int which);
bool	apply_swap(t_ps foo, t_ps bar, int which);
bool	apply_rotation(t_ps foo, t_ps bar, int which);
bool	apply_rev_rotation(t_ps foo, t_ps bar, int which);
int		apply_which(const char *op, int *which);

#endif /* OP_H */
