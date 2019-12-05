/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:18:04 by archid-           #+#    #+#             */
/*   Updated: 2019/11/28 20:52:50 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUMP_H
# define DUMP_H

# include "ps.h"
# include "op.h"
# include "reader.h"

void	dump_ops(t_lst ops, t_flags *flags);
void	dump_stacks(t_ps a, t_ps b);
void	dump_state(t_ps a, t_ps b, t_lst ops, t_ps_node *node);
void	ps_dump(t_ps ps);

#endif
