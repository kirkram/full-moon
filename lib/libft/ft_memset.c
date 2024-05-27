/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:54:31 by klukiano          #+#    #+#             */
/*   Updated: 2024/01/16 16:14:34 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	*ft_memset(void *str, int c, size_t len)
{
	unsigned char	newchar;
	unsigned char	*newstr;

	newchar = (unsigned char)c;
	newstr = (unsigned char *)str;
	while (len > 0)
	{
		*newstr = newchar;
		newstr ++;
		len --;
	}
	return (str);
}
