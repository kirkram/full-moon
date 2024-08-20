/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:22:16 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/20 18:22:26 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdlib.h>

void *ft_realloc(void *ptr, size_t new_size) 
{
    void	*new_ptr;

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
        ft_memcpy(new_ptr, ptr, new_size);
        free(ptr);
    }
    return (new_ptr);
}