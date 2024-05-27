/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:14:14 by klukiano          #+#    #+#             */
/*   Updated: 2024/01/16 16:14:15 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strchr(char *str, int c)
{
	c = (char)c;
	while (*str != c && *str != '\0')
		str ++;
	if (*str == '\0' && c != '\0')
		return (NULL);
	else
		return (str);
}
