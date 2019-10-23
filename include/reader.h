/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 04:08:01 by archid-           #+#    #+#             */
/*   Updated: 2019/10/23 04:08:34 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

# define BUFF_SIZE 32

# include "op.h"

t_list			*read_input(void);

t_ps			read_args(int ac, char**av);

#endif /* READER_H */
