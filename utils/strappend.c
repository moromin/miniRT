/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strappend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:01:46 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 20:01:46 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*strappend(char *dst, const char *src, size_t l)
{
	char	*rtn;
	size_t	i;
	size_t	j;
	size_t	k;

	rtn = (char *)malloc(sizeof(char) * (ft_strlen(dst) + l + 1));
	if (!rtn)
		return (NULL);
	i = 0;
	j = 0;
	while (dst[j])
		rtn[i++] = dst[j++];
	k = 0;
	while (k < l)
		rtn[i++] = src[k++];
	rtn[i] = '\0';
	free(dst);
	return (rtn);
}
