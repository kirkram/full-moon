/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:32:19 by klukiano          #+#    #+#             */
/*   Updated: 2023/11/17 13:23:35 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	size;

	size = ft_strlen(s1);
	copy = malloc((size + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	ft_memcpy(copy, s1, size + 1);
	return (copy);
}
