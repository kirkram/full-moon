/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:22:16 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/20 16:37:04 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdlib.h>

void *ft_realloc(void *ptr, size_t old_size, size_t new_size) 
{
    void	*new_ptr;
	size_t	copy_size;

    if (new_size == 0) 
	{
        free(ptr);
        return NULL;
    }
    new_ptr = (void *)malloc(new_size);
    if (!new_ptr)
        return NULL;
    if (ptr) 
	{
		if (old_size < new_size)
        	copy_size = old_size;
		else
			copy_size = new_size;
        ft_memcpy(new_ptr, ptr, copy_size);
        free(ptr);
    }
    return (new_ptr);
}