/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:55:23 by mburakow          #+#    #+#             */
/*   Updated: 2024/07/04 15:02:27 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int	read_rgb_color_value(char *line, t_data *data)
{
	char			**value_array;
	int				len;
	unsigned int	rgb[3];
	unsigned int	color;
	int				i;

	value_array = ft_split(line, ',');
	len = 0;
	while (value_array[len] != NULL)
		len++;
	if (len != 3)
		map_validation_error("Error: invalid map parameter", 0, line, data);
	i = -1;
	while (++i < len)
		rgb[i] = ft_atoi(value_array[i]);
	i = -1;
	while (++i < len)
	{
		if (rgb[i] > 255)
			map_validation_error("Error: invalid map parameter", 0, line, data);
	}
	color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (color);
}

static void	read_our_parameter_type(char *line, t_data *data)
{
	char	*value_start;

	value_start = ft_strchr(line, 61) + 1;
	if (value_start && (ft_strcpos(value_start, '\n') != -1))
		value_start[ft_strcpos(value_start, '\n')] = '\0';
	if (line[1] == 'N')
		data->nsew_path[0] = ft_strjoin("./textures/", value_start);
	else if (line[1] == 'S')
		data->nsew_path[1] = ft_strjoin("./textures/", value_start);
	else if (line[1] == 'E')
		data->nsew_path[2] = ft_strjoin("./textures/", value_start);
	else if (line[1] == 'W')
		data->nsew_path[3] = ft_strjoin("./textures/", value_start);
	else if (line[1] == 'C' || line[1] == 'F')
	{
		if (is_valid_hex(value_start))
		{
			if (line[1] == 'C')
				data->ceilingcolor = ft_atoh(value_start);
			else if (line[1] == 'F')
				data->floorcolor = ft_atoh(value_start);
		}
		else
			map_validation_error("Error: invalid map parameter", 0, line, data);
	}
}

static void	read_subject_parameter_type(char *line, t_data *data)
{
	char	*value_start;

	value_start = &line[2];
	if (value_start && (ft_strcpos(value_start, '\n') != -1))
		value_start[ft_strcpos(value_start, '\n')] = '\0';
	while (*value_start == ' ')
		value_start++;
	printf("Reading value: %s\n", value_start);
	if (line[0] == 'N')
		data->nsew_path[0] = ft_strjoin("./textures/", value_start);
	else if (line[0] == 'S')
		data->nsew_path[1] = ft_strjoin("./textures/", value_start);
	else if (line[0] == 'E')
		data->nsew_path[2] = ft_strjoin("./textures/", value_start);
	else if (line[0] == 'W')
		data->nsew_path[3] = ft_strjoin("./textures/", value_start);
	else if (line[0] == 'C' || line[0] == 'F')
	{
		printf("Reading color value: %s\n", value_start);
		if (line[0] == 'C')
			data->ceilingcolor = read_rgb_color_value(value_start, data);
		else if (line[0] == 'F')
			data->floorcolor = read_rgb_color_value(value_start, data);
	}
	else
		map_validation_error("Error: invalid map parameter", 0, line, data);
}

void	read_map_parameter(char *line, t_data *data)
{
	if (line[0] == '\n')
		return ;
	if ((line[0] == 'T' && (line[1] == 'N' || line[1] == 'E' || line[1] == 'S'
				|| line[1] == 'W') && line[2] == '=') || (line[0] == 'C'
			&& (line[1] == 'C' || line[1] == 'F') && line[2] == '='))
		read_our_parameter_type(line, data);
	else if ((((line[0] == 'N' && line[1] == 'O') || (line[0] == 'E'
					&& line[1] == 'A') || (line[0] == 'S' && line[1] == 'O')
				|| (line[0] == 'W' && line[1] == 'E')) && line[2] == ' ')
		|| ((line[0] == 'F' || line[0] == 'C') && line[1] == ' '))
		read_subject_parameter_type(line, data);
	else
		map_validation_error("Error: invalid map parameter", 0, line, data);
}

/*
void	read_map_parameter(char *line, t_data *data)
{
	char	*value_start;

	if (line[0] == '\n')
		return ;
	if (line[0] != 'T' || !(line[1] == 'N' || line[1] == 'E' || line[1] == 'S'
			|| line[1] == 'W') || line[2] != '=')
	{
		if (line[0] != 'C' || !(line[1] == 'C' || line[1] == 'F')
			|| line[2] != '=')
			map_validation_error("Error: invalid map parameter", 0, line, data);
	}
	value_start = ft_strchr(line, 61) + 1;
	if (value_start && (ft_strcpos(value_start, '\n') != -1))
		value_start[ft_strcpos(value_start, '\n')] = '\0';
	else
		map_validation_error("Error: invalid map parameter", 0, line, data);
	if (line[1] == 'N')
		data->nsew_path[0] = ft_strjoin("./textures/", value_start);
	else if (line[1] == 'S')
		data->nsew_path[1] = ft_strjoin("./textures/", value_start);
	else if (line[1] == 'E')
		data->nsew_path[2] = ft_strjoin("./textures/", value_start);
	else if (line[1] == 'W')
		data->nsew_path[3] = ft_strjoin("./textures/", value_start);
	else if (line[1] == 'C' || line[1] == 'F')
	{
		if (is_valid_hex(value_start))
		{
			if (line[1] == 'C')
				data->ceilingcolor = ft_atoh(value_start);
			else if (line[1] == 'F')
				data->floorcolor = ft_atoh(value_start);
		}
		else
			map_validation_error("Error: invalid map parameter", 0, line, data);
	}
}
*/