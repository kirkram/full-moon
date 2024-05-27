/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:14:40 by klukiano          #+#    #+#             */
/*   Updated: 2024/01/16 16:13:28 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strrchr(char *str, int c)
{
	int	chk;

	c = (char)c;
	chk = 0;
	while (*str != '\0')
	{
		if (*str == c)
			chk = 1;
		str ++;
	}
	if (c == '\0')
		return (str);
	if (chk == 0)
		return (NULL);
	while (*str != c)
		str --;
	return (str);
}
