/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:29:17 by klukiano          #+#    #+#             */
/*   Updated: 2024/01/16 16:13:32 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strnstr(const char *h1, const char *ndl, size_t len)
{
	int		i;
	size_t	tmp;

	if (!h1 && len == 0)
		return (NULL);
	if (*ndl == '\0')
		return ((char *)h1);
	while (*h1 != '\0' && len > 0)
	{
		i = 0;
		tmp = len;
		while (h1[i] == ndl[i] && ndl[i] != '\0' && len > 0)
		{
			i ++;
			len --;
		}
		if (ndl[i] == '\0')
			return ((char *)h1);
		else
			len = tmp;
		h1 ++;
		len --;
	}
	return (NULL);
}
