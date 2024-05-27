/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:04:05 by klukiano          #+#    #+#             */
/*   Updated: 2024/01/16 16:14:21 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		**ft_split(char const *str, char c);
static int	splitlen(char *str, char c);
static int	countstrings(char *str, char c);
static char	**splitter(char *str, char c, char **array);
static char	**free_reverse(int i, char **array);

char	**ft_split(char const *str, char c)
{
	char	**array;

	if (str)
	{
		array = malloc((countstrings((char *)str, c) + 1) * sizeof(char *));
		if (array == NULL)
			return (NULL);
		if (!countstrings((char *)str, c))
			array[0] = NULL;
		else
			splitter((char *)str, c, array);
		return (array);
	}
	return (NULL);
}

static char	**splitter(char *str, char c, char **array)
{
	int	i;
	int	j;

	i = 0;
	while (*str != '\0')
	{
		j = 0;
		while (*str == c)
			str ++;
		array[i] = malloc(splitlen((char *)str, c) + 1 * sizeof(char));
		if (array[i] == NULL)
			return (free_reverse(i, array));
		while (*str != c && *str != '\0')
		{
			array[i][j] = *str;
			j ++;
			str ++;
		}
		array[i][j] = '\0';
		while (*str == c && *str != '\0')
			str ++;
		i ++;
	}
	array[i] = NULL;
	return (array);
}

static int	splitlen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i ++;
	return (i);
}

static	int	countstrings(char *str, char c)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		while (*str == c && *str != '\0')
			str ++;
		if (*str != '\0')
			count ++;
		while (*str != c && *str != '\0')
			str ++;
	}
	return (count);
}

static char	**free_reverse(int i, char **array)
{
	while (i >= 0)
	{
		free (array[i]);
		i --;
	}
	free (array);
	return (NULL);
}
