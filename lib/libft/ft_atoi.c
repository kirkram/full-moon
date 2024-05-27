/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:30:59 by klukiano          #+#    #+#             */
/*   Updated: 2024/05/03 15:46:26 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str ++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str ++;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - 48;
		if (num < 0 || num > 2147483647)
		{
			if (num == 2147483648 && sign < 0)
				return (num * sign);
			if (sign > 0)
				return (-1);
			return (0);
		}
		str ++;
	}
	return (num * sign);
}
