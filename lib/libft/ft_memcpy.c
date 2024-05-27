/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:38:48 by klukiano          #+#    #+#             */
/*   Updated: 2024/01/16 16:14:42 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	if (dst || src)
	{
		while (n > 0)
		{
			((unsigned char *)dst)[n - 1] = ((unsigned char *)src)[n - 1];
			n --;
		}
	}
	return (dst);
}
