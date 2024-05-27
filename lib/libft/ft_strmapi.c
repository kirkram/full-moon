/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:08:54 by klukiano          #+#    #+#             */
/*   Updated: 2024/01/16 16:13:39 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*copy;
	int		i;

	if (s && f)
	{
		i = 0;
		copy = malloc((ft_strlen((char *)s) + 1) * sizeof(*s));
		if (copy == NULL)
			return (NULL);
		while (s[i] != '\0')
		{
			copy[i] = f(i, s[i]);
			i ++;
		}
		copy[i] = '\0';
		return (copy);
	}
	return (NULL);
}
