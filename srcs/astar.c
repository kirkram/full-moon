/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:15:56 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/28 13:48:41 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "pathfinding.h"

int	node_is_target(t_node *current, t_coord end_pos,
		t_astar *context)
{
	if (current->x == end_pos.x && current->y == end_pos.y)
		return (1);
	context->closed_set[current->y][current->x] = 1;
	return (0);
}

void	process_neighbors(t_node *current, t_astar *context, t_data *data,
		t_coord end_pos)
{
	int		i;
	t_coord	new_coord;
	int		new_g;
	t_node	*neighbor;

	i = -1;
	while (++i < 8)
	{
		new_coord.x = current->x + context->directions[i][0];
		new_coord.y = current->y + context->directions[i][1];
		if (is_in_bounds(new_coord.x, new_coord.y, data)
			&& !context->closed_set[new_coord.y][new_coord.x]
			&& is_walkable(new_coord.x, new_coord.y, data))
		{
			if (i < 4)
				new_g = current->g + COST_STRAIGHT;
			else
				new_g = current->g + COST_DIAGONAL;
			neighbor = create_node(new_coord, new_g, heuristic(new_coord.x,
						new_coord.y, end_pos.x, end_pos.y), current);
			if (!neighbor)
				error_a_star(context, data);
			pq_push(context->open_set, neighbor, context, data);
			free(neighbor);
			neighbor = NULL;
		}
	}
}

int	process_current_node(t_node *current, t_coord end_pos, t_astar *context,
		t_data *data)
{
	if (node_is_target(current, end_pos, context))
		return (1);
	process_neighbors(current, context, data, end_pos);
	return (0);
}

t_route	*run_a_star(t_astar *context, t_coord end_pos, t_data *data)
{
	t_node	*current;

	current = NULL;
	while (context->open_set->size > 0)
	{
		current = pq_pop(context->open_set, context, data);
		add_node_to_list(context->closed_list, current);
		if (process_current_node(current, end_pos, context, data))
		{
			context->route = reconstruct_path(current);
			return (context->route);
		}
	}
	return (NULL);
}

t_route	*a_star(t_coord start_pos, t_coord end_pos, t_data *data)
{
	t_astar	*context;
	t_route	*route;

	context = initialize_a_star(start_pos, data);
	route = run_a_star(context, end_pos, data);
	printf("Returned for cleanup.\n");
	cleanup_a_star(context, data);
	return (route);
}

/*
t_route	*a_star(t_coord start_pos, t_coord end_pos, t_data *data)
{
	t_priorityqueue	*open_set;
	int				**closed_set;
	t_node			*start_node;
	t_node			*current;
	t_node			*neighbor;
	t_route			*route;
	int				i;
	int				new_x;
	int				new_y;
	int				new_g;
	int				new_h;
	int				directions[8][2];

	set_directions(directions);
	open_set = pq_create(200);
	closed_set = initialize_closed_set(data);
	start_node = create_node(start_pos.x, start_pos.y, 0, 0, NULL);
	pq_push(open_set, start_node);
	while (open_set->size > 0)
	{
		current = pq_pop(open_set);
		if (current->x == end_pos.x && current->y == end_pos.y)
		{
			route = reconstruct_path(current);
			free(current);
			break ;
		}
		closed_set[current->y][current->x] = 1;
		i = -1;
		while (++i < 8)
		{
			new_x = current->x + directions[i][0];
			new_y = current->y + directions[i][1];
			if (is_in_bounds(new_x, new_y, data) && !closed_set[new_y][new_x]
				&& is_walkable(new_x, new_y, data))
			{
				if (i < 4)
					new_g = current->g + COST_STRAIGHT;
				else
					new_g = current->g + COST_DIAGONAL;
				new_h = heuristic(new_x, new_y, end_pos.x, end_pos.y);
				neighbor = create_node(new_x, new_y, new_g, new_h, current);
				pq_push(open_set, neighbor);
			}
		}
	}
	i = -1;
	while (++i < data->map_height)
		free(closed_set[i]);
	free(closed_set);
	free(open_set->nodes);
	free(open_set);
	return (route);
}

extra stuff:
void	invert_2d_array(int **array, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			array[i][j] = array[i][j] == 1 ? 0 : 1;
		}
	}
}

int	main(void)
{
	t_data	data;
	t_coord	*route;
	int		i;
	int		j;

	int map[9][10] = {
		{1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
		{1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
		{1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
		{0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
		{1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
		{1, 0, 1, 1, 1, 1, 0, 1, 0, 0},
		{1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 0, 0, 0, 1, 0, 0, 1}
	};
	data.map_height = 9;
	data.map_width = 10;
	data.world_map = (int**)malloc(data.map_height * sizeof(int*));
	i = -1;
	while (++i < data.map_height)
	{
		j = -1;
		data.world_map[i] = (int*)malloc(data.map_width * sizeof(int));
		while (++j < data.map_width)
			data.world_map[i][j] = map[i][j];
	}
	invert_2d_array(data.world_map, 9, 10);
	print_map(&data);
	route = a_star(0, 0, 8, 7, &data);
	i = -1;
	printf("result: \n");
	while (route[++i].x != -1)
		printf("C: %d x: %d y: %d\n", i, route[i].x, route[i].y);
	i = -1;
	while (++i < data.map_height)
		free(data.world_map[i]);
	free(data.world_map);
	return (0);
}

void	print_2d_int(int **int_arr, int rows, int cols)
{
	int	y;
	int	x;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			dprintf(2, "%d", int_arr[y][x]);
			x++;
		}
		dprintf(2, "\n");
		y++;
	}
	dprintf(2, "\n");
}
*/