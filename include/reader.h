/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 04:08:01 by archid-           #+#    #+#             */
/*   Updated: 2019/11/17 16:35:14 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

# include "op.h"

# define DEBUG_READ					1

t_lst			read_input(void);
t_ps			read_args(int ac, char **av);

#endif /* READER_H */
