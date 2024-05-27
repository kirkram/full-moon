/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:05:57 by klukiano          #+#    #+#             */
/*   Updated: 2024/01/16 16:15:19 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_itoa(int n);
static char	*ft_recursion(int n, char *array, int i);
static int	ft_intlen(int n);

char	*ft_itoa(int n)
{
	char	*array;
	int		len;

	len = ft_intlen(n);
	array = malloc((len + 1) * sizeof(char));
	if (array == NULL)
		return (NULL);
	array = ft_recursion(n, array, len - 1);
	array[len] = '\0';
	return (array);
}

static char	*ft_recursion(int n, char *array, int i)
{
	if (n == -2147483648)
	{
		n = n / 10;
		array [i] = '8';
		i --;
	}
	if (n < 0)
	{
		array[0] = '-';
		n = -n;
	}
	if (n > 9)
		ft_recursion(n / 10, array, i - 1);
	array[i] = n % 10 + '0';
	return (array);
}

static int	ft_intlen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i ++;
	while (n != 0)
	{
		n = n / 10;
		i ++;
	}
	return (i);
}
