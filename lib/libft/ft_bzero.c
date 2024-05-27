/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:37:44 by klukiano          #+#    #+#             */
/*   Updated: 2024/01/16 16:15:42 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_bzero(void *str, size_t n)
{
	if (n == 0)
		return ;
	while (n > 0)
	{
		*(unsigned char *)str = '\0';
		str ++;
		n --;
	}
	return ;
}
