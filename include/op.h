/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 04:57:57 by archid-           #+#    #+#             */
/*   Updated: 2019/10/19 15:45:05 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

#include "libft.h"

#define WHICH_HELPER(c)				(c == 'a' ? OP_TO_A : OP_TO_B)

/*
** Data Structures
*/

enum e_ops
{
	OP_PUSH = 0, OP_SWAP,
	OP_REV, OP_RREV, OP_NIL,

	OP_TO_A = 0,
	OP_TO_B, OP_TO_BOTH
};

typedef struct	s_op
{
	enum e_ops	op;
	int			which;
}				t_op;

typedef t_s32	t_val;

/*
** Function Prototypes
*/

bool	is_op(const char *buffer);

t_op	op_which(const char *op);
bool	op_push(t_lst *foo, t_lst *bar, t_op op);
bool	op_swap(t_lst *foo, t_lst *bar, t_op op);
bool	op_rotation(t_lst *foo, t_lst *bar, t_op op);
bool	op_rev_rotation(t_lst *foo, t_lst *bar, t_op op);

void	do_psh(t_lst *stack_dest, t_lst *stack_src);
void	do_swp(t_lst *stack);
void	do_rot(t_lst *stack, bool isup);

#endif
