/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:16:37 by archid-           #+#    #+#             */
/*   Updated: 2019/10/22 03:21:44 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include "ps.h"

enum e_which_stack
{
	ON_A = 0,
	ON_B, ON_BOTH
};

bool	op_which(t_ps foo, t_ps bar, int which);

bool	op_dopsh(t_ps dest, t_ps src);
bool	op_doswp(t_ps stack);
bool	op_dorot(t_ps stack);
bool	op_dorrot(t_ps stack);

#endif /* OP_H */
