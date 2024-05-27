/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:14:43 by klukiano          #+#    #+#             */
/*   Updated: 2023/12/26 14:50:39 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		while (*s != '\0')
		{
			write (fd, &*s, 1);
			s ++;
		}
	}
	write (fd, "\n", 1);
}
