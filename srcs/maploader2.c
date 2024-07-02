/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maploader2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:05:11 by mburakow          #+#    #+#             */
/*   Updated: 2024/07/02 19:12:20 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	replace_tabs_with_spaces(const char *input_line, char *output_line)
{
	int	i;
	int	j;
	int	input_len;
	int	output_index;
	int	space_count;

	input_len = ft_strlen(input_line);
	output_index = 0;
	i = -1;
	while (++i < input_len)
	{
		if (input_line[i] == '\t')
		{
			space_count = TAB_WIDTH - (output_index % TAB_WIDTH);
			j = -1;
			while (++j < space_count)
				output_line[output_index++] = ' ';
		}
		else
			output_line[output_index++] = input_line[i];
	}
	output_line[output_index] = '\0';
}

void	convert_tabs(char **line)
{
	char	output_line[MAX_MAPWIDTH * TAB_WIDTH];

	replace_tabs_with_spaces(*line, output_line);
	free(*line);
	*line = ft_strdup(output_line);
}
