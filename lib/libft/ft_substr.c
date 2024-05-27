/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:38:51 by klukiano          #+#    #+#             */
/*   Updated: 2023/11/20 12:02:02 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	sub_len;

	if (!s)
		return (NULL);
	sub_len = ft_strlen(s);
	if (sub_len < start)
	{
		sub = malloc(1);
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	sub_len = sub_len - start;
	if (sub_len > len)
		sub_len = len;
	sub = malloc((sub_len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, (char *)s + start, sub_len + 1);
	return (sub);
}
