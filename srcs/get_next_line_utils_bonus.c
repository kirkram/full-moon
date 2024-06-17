/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 03:20:12 by mburakow          #+#    #+#             */
/*   Updated: 2024/06/14 21:28:41 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	gnl_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}

static char	*join_strs(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (str);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		if (s1)
			s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = join_strs(s1, s2);
	free(s1);
	return (str);
}

int	gnl_strcpos(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

char	*gnl_substr(char *buffer, unsigned int start, size_t len)
{
	char	*new;
	size_t	slen;
	size_t	i;

	if (!buffer)
		return (NULL);
	slen = ft_strlen((char *)buffer);
	if (start > slen)
		len = 0;
	else if (slen - start < len)
		len = slen - start;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	new[len] = '\0';
	i = 0;
	while (i < len && start < slen)
	{
		new[i] = buffer[start + i];
		i++;
	}
	return (new);
}
