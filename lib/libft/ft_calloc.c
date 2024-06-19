/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:31:22 by klukiano          #+#    #+#             */
/*   Updated: 2024/05/03 15:41:54 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	buf_size;

	buf_size = SIZE_MAX;
	if (count != 0)
	{
		if (buf_size / count < size)
			return (NULL);
	}
	buf_size = count * size;
	ptr = malloc(buf_size);
	if (!ptr)
		return (NULL);
	ft_bzero (ptr, buf_size);
	return (ptr);
}
