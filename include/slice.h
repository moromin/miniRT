/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:57:24 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 20:02:12 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLICE_H
# define SLICE_H

# include <stdlib.h>
# include <assert.h>
# include "../libft/libft.h"
# include "../wrapper/x.h"

typedef struct s_slice	t_slice;

// slice.c
t_slice	*make(size_t size, size_t len, size_t cap);
void	delete(t_slice *s);
void	append(t_slice *s, void *elem);
void	*get(t_slice *s, int index);
size_t	len(t_slice *s);

// slice_x.c
void	delete_recursively(t_slice *s, int depth);
void	*get_x2(t_slice *s, int i1, int i2);

#endif
