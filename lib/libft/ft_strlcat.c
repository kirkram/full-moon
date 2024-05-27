/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:12:11 by klukiano          #+#    #+#             */
/*   Updated: 2024/01/16 16:13:54 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;
	size_t	j;

	if ((!dst || !src) && dstsize == 0)
		return (0);
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	if (len_dst >= dstsize)
		return (len_src + dstsize);
	i = len_dst;
	j = 0;
	while (j < dstsize - len_dst - 1 && src[j] != '\0')
	{
		dst[i] = src[j];
		i ++;
		j ++;
	}
	dst[i] = '\0';
	return (len_dst + len_src);
}
