/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:28:26 by klukiano          #+#    #+#             */
/*   Updated: 2024/01/16 16:13:35 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 == *s2 && n > 0 && *s1 && *s2)
	{
		s1 ++;
		s2 ++;
		n --;
	}
	if (n == 0)
		return (0);
	return ((int)((unsigned char)*s1 - (unsigned char)*s2));
}
