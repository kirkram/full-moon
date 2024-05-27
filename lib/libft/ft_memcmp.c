/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:29:34 by klukiano          #+#    #+#             */
/*   Updated: 2024/01/16 16:14:45 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	if (n == 0)
		return (0);
	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while (n > 0 && *ptr1 == *ptr2)
	{
		ptr1 ++;
		ptr2 ++;
		n --;
	}
	if (n == 0)
		return (0);
	else
		return (((unsigned char)*ptr1 - *ptr2));
}
