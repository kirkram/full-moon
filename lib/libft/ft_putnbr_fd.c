/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:15:09 by klukiano          #+#    #+#             */
/*   Updated: 2023/12/26 14:50:44 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void		ft_putnbr_fd(int n, int fd);
static void	putchar_fd(char c, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		putchar_fd('-', fd);
		putchar_fd('2', fd);
		n = 147483648;
	}
	if (n < 0)
	{
		n = -n;
		putchar_fd('-', fd);
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	putchar_fd(n % 10 + '0', fd);
}

static void	putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}
