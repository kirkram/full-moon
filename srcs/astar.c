/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:15:56 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/17 14:15:26 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "pathfinding.h"

t_priorityqueue* pq_create(int capacity) 
{
    t_priorityqueue* pq;

	pq = (t_priorityqueue*)malloc(sizeof(t_priorityqueue));
	/*
	if (!pq)
		free_all_and_quit(data);
	*/
    pq->nodes = (t_node*)malloc(capacity * sizeof(t_node));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void print_node(t_node *node)
{
	printf("PQ x:%d\ty:%d\tg:%d\th:%d\tf:%d", node->x, node->y, node->g, node->h, node->f);
	if(node->parent)
	{
		printf("\tpx:%d\tpy:%d", node->parent->x, node->parent->y);
	}
	printf("\n");	
}

void print_priority_queue(t_priorityqueue *pq) 
{
    int i;

	i = -1;
	while (++i < pq->size)
		print_node(&pq->nodes[i]);
}

void pq_swap(t_node *a, t_node *b)
{
    t_node temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	heapify_up(t_priorityqueue *pq, int i)
{
    if (i && pq->nodes[(i - 1) / 2].f > pq->nodes[i].f) {
        pq_swap(&pq->nodes[(i - 1) / 2],
             &pq->nodes[i]);
        heapify_up(pq, (i - 1) / 2);
    }
}

void	pq_push(t_priorityqueue *pq, t_node *node)
{
	if (pq->size >= pq->capacity)
	{
		// forbidden function!
        pq->capacity *= 2;
        pq->nodes = (t_node *)realloc(pq->nodes, pq->capacity * sizeof(t_node));
    }
	pq->nodes[pq->size++] = *node;
	heapify_up(pq, pq->size - 1);
}

void	heapify_down(t_priorityqueue *pq, int i)
{
    int smallest;
    int left;
    int right;

	smallest = i;
	left = 2 * i + 1;
	right = 2 * i + 2;
    if (left < pq->size
        	&& pq->nodes[left].f < pq->nodes[smallest].f)
        smallest = left;
    if (right < pq->size
        	&& pq->nodes[right].f < pq->nodes[smallest].f)
        smallest = right;
    if (smallest != i) {
        pq_swap(&pq->nodes[i], &pq->nodes[smallest]);
        heapify_down(pq, smallest);
    }
}

t_node* pq_pop(t_priorityqueue *pq)
{
	t_node	*result;

    if (!pq->size) 
	{
        printf("pq_pop: Priority queue is empty\n");
        return NULL;
    }
    result = (t_node*)malloc(sizeof(t_node));
    *result = pq->nodes[0];
    pq->nodes[0] = pq->nodes[--pq->size];
    heapify_down(pq, 0);
    return result;
}

t_node	*peek(t_priorityqueue *pq)
{
	if (!pq->size) 
	{
        printf("peek: Priority queue is empty\n");
        return NULL;
    }
	return (&pq->nodes[0]);
}

t_node* create_node(int x, int y, int g, int h, t_node *parent) 
{
    t_node* node; 
    
    node = (t_node*)malloc(sizeof(t_node));
    node->x = x;
    node->y = y;
    node->g = g;
    node->h = h;
    node->f = g + h;
	node->parent = parent;
    return node;
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int heuristic(int x1, int y1, int x2, int y2) 
{
	int	dx;
	int	dy;
    
	dx = abs(x1 - x2);
	dy = abs(y1 - y2);
    return (COST_STRAIGHT * (dx + dy) + (COST_DIAGONAL - 2 * COST_STRAIGHT) * min(dx, dy));
}

bool is_in_bounds(int x, int y, t_data *data) 
{
    return (x >= 0 && x < data->map_width && y >= 0 && y < data->map_height);
}

bool is_walkable(int x, int y, t_data *data) 
{
    return (is_in_bounds(x, y, data) && data->world_map[y][x] == 0);
}

t_route *reconstruct_path(t_node* end_node)
{
    t_node  *current;
	t_route	*route;
    int     count;

    current = end_node;
	route = (t_route *)malloc(sizeof(t_route));
    route->size = -1;
    while (current) 
	{
        route->size++;
        current = current->parent;
    }
    route->coords = (t_coord *)malloc(sizeof(t_coord) * (route->size + 1));
    route->coords[route->size].x = -1;
    route->coords[route->size].y = -1;
	current = end_node;
	count = route->size;
    while (current && count >= 1) 
	{
        count--;
        route->coords[count].x = current->x;
        route->coords[count].y = current->y;
        printf("C: %d x: %d y: %d\n", count, route->coords[count].x, route->coords[count].y);
        current = current->parent;
		if (current->parent == NULL)
			break ;
    }
    return (route);
}

void    print_map(t_data *data) 
{
    int y;
    int x;

    y = -1;
    while (++y < data->map_height) 
	{
        x = -1;
        while (++x < data->map_width) 
            printf("%d ", data->world_map[y][x]);
        printf("\n");
    }
}

static void	set_directions(int directions[8][2])
{
	directions[0][0] = 0; directions[0][1] = 1;
	directions[1][0] = 1; directions[1][1] = 0;
	directions[2][0] = 0; directions[2][1] = -1;
	directions[3][0] = -1; directions[3][1] = 0;
	directions[4][0] = 1; directions[4][1] = 1;
	directions[5][0] = 1; directions[5][1] = -1;
	directions[6][0] = -1; directions[6][1] = -1;
	directions[7][0] = -1; directions[7][1] = 1;
}

static int	**initialize_closed_set(t_data *data)
{
	int	i;
	int	**closed_set;

	// change forbidden functions
	closed_set = (int **)calloc(data->map_height, sizeof(int *));
	// malloc protect
    i = -1;
    while (++i < data->map_height)
		closed_set[i] = (int *)calloc(data->map_width, sizeof(int));
		// malloc protect
	return (closed_set);
}

t_route *a_star(int start_x, int start_y, int end_x, int end_y, t_data *data) 
{
    t_priorityqueue	*open_set;
	int 			**closed_set;
	t_node			*start_node;
	t_node			*current;
	t_node			*neighbor;
    t_route         *route;
    int             i;
    int             new_x;
    int             new_y;
    int             new_g;
    int             new_h;
	int				directions[8][2];
	
	set_directions(directions);
	open_set = pq_create(200);
	closed_set = initialize_closed_set(data);
    start_node = create_node(start_x, start_y, 0, 0, NULL);
    pq_push(open_set, start_node);
    while (open_set->size > 0) 
	{
        current = pq_pop(open_set);
        if (current->x == end_x && current->y == end_y) 
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
            if (is_in_bounds(new_x, new_y, data) && !closed_set[new_y][new_x] && is_walkable(new_x, new_y, data)) 
			{
                if (i < 4)
                    new_g = current->g + COST_STRAIGHT;
                else
                    new_g = current->g + COST_DIAGONAL;
                new_h = heuristic(new_x, new_y, end_x, end_y);
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

/* extra stuff:
void invert_2d_array(int **array, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = array[i][j] == 1 ? 0 : 1;
        }
    }
}

int main() 
{
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
    t_data  data;
    t_coord *route;
    int     i;
    int     j;

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