#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define COST_STRAIGHT 10
#define COST_DIAGONAL 14

typedef struct s_node 
{
    int x;
	int y;
	int g; 
	int h;
	int f;
	int px;
	int py;
    struct s_node* parent;
} t_node;

typedef struct s_priorityqueue
{
    t_node* nodes;
    int size;
	int capacity;
} t_priorityqueue;

typedef struct s_data
{
    int **world_map;
    int map_width;
	int map_height;
} t_data;

t_priorityqueue* pq_create(int capacity) {
    t_priorityqueue* pq = (t_priorityqueue*)malloc(sizeof(t_priorityqueue));
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
	printf("before swap:\n");
	print_node(a);
	print_node(b);
	temp = *a;
	*a = *b;
	*b = temp;
	printf("after swap:\n");
	print_node(a);
	print_node(b);
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

t_node* create_node(int x, int y, int g, int h, t_node *parent) {
    t_node* node = (t_node*)malloc(sizeof(t_node));
    node->x = x;
    node->y = y;
    node->g = g;
    node->h = h;
    node->f = g + h;
	node->px = 0;
	node->py = 0;
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

t_node *find_by_coordinates(int x, int y, t_priorityqueue *pq)
{
	int	i;

	i = -1;
	while (++i < pq->size)
	{
		if (x == pq->nodes[i].x && y == pq->nodes[i].y)
			return (&pq->nodes[i]);
	}
	printf("Node x%d y%d not found!!!", x, y);
	return (NULL);
}

void reconstruct_path(t_node* end_node, t_priorityqueue *pq, t_data *data) 
{
    t_node* current;

	(void)pq;
	printf("Reconstructing path\n");
	current = end_node;
    while (current) 
	{
        data->world_map[current->y][current->x] = 8;
		printf("PQ:\tx:%d\ty:%d\tg:%d\th:%d\tf:%d\n", current->x, current->y, current->g, current->h, current->f);
        //current = find_by_coordinates(current->x, current->y, pq);
		current = current->parent;
    }
}

void print_map(t_data *data) 
{
    for (int y = 0; y < data->map_height; y++) 
	{
        for (int x = 0; x < data->map_width; x++) 
            printf("%d ", data->world_map[y][x]);
        printf("\n");
    }
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

void a_star(int start_x, int start_y, int end_x, int end_y, t_data *data) 
{
    t_priorityqueue	*open_set;
	int 			**closed_set;
	t_node			*start_node;
	t_node			*current;
	t_node			*neighbor;
	int				found;
	
	found = 0;
	open_set = pq_create(200); // should be dynamic size
	// change forbidden functions
    closed_set = (int **)calloc(data->map_height, sizeof(int *));
    for (int i = 0; i < data->map_height; i++) 
		closed_set[i] = (int *)calloc(data->map_width, sizeof(int));
	//printf("Closed set:\n");
	//print_2d_int(closed_set, 9, 10);
    start_node = create_node(start_x, start_y, 0, 0, NULL);
    pq_push(open_set, start_node);
	// edit this:
    int directions[8][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1} };
    while (open_set->size > 0) 
	{
        current = pq_pop(open_set);
		//printf("current: x%d y%d\n", current->x, current->y);
        if (current->x == end_x && current->y == end_y) 
		{
			printf("Path found!!!\n");
			//printf("Closed set:\n");
			//print_2d_int(closed_set, 9, 10);
			//printf("Priority queue:\n");
			//print_priority_queue(open_set);
            reconstruct_path(current, open_set, data);
            print_map(data);
            free(current);
			found = 1;
            break ;
        }
        closed_set[current->y][current->x] = 1;
        for (int i = 0; i < 8; i++) {
            int new_x = current->x + directions[i][0], new_y = current->y + directions[i][1];
            if (is_in_bounds(new_x, new_y, data) && !closed_set[new_y][new_x] && is_walkable(new_x, new_y, data)) 
			{
				/*
				if (i >= 4) {
                    int adj1_x = current->x + directions[i][0], adj1_y = current->y;
                    int adj2_x = current->x, adj2_y = current->y + directions[i][1];
                    if (!is_walkable(adj1_x, adj1_y, data) || !is_walkable(adj2_x, adj2_y, data)) continue;
                }
				*/
                int new_g = current->g + (i < 4 ? COST_STRAIGHT : COST_DIAGONAL);
                int new_h = heuristic(new_x, new_y, end_x, end_y);
                neighbor = create_node(new_x, new_y, new_g, new_h, current);
				neighbor->px = current->x;
				neighbor->py = current->y;
				//printf("Pushed to open set: x%d, y%d, g%d, h%d, px%d, py%d\n", new_x, new_y, new_g, new_h, current->x, current->y);
				pq_push(open_set, neighbor);
            }
        }
		// important
        free(current);
    }
	if (!found)
	{
		printf("No path found!\n");
		//printf("Closed set:\n");
		//print_2d_int(closed_set, 9, 10);
		//printf("Map:\n");
		//print_2d_int(data->world_map, 9, 10);
	}
    for (int i = 0; i < data->map_height; i++) free(closed_set[i]);
    free(closed_set);
    free(open_set->nodes);
    free(open_set);
}

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

    t_data data;
    data.map_height = 9;
    data.map_width = 10;
    data.world_map = (int**)malloc(data.map_height * sizeof(int*));
    for (int i = 0; i < data.map_height; i++) {
        data.world_map[i] = (int*)malloc(data.map_width * sizeof(int));
        for (int j = 0; j < data.map_width; j++) {
            data.world_map[i][j] = map[i][j];
        }
    }
	invert_2d_array(data.world_map, 9, 10);
	//printf("Starting map:\n");
	//print_map(&data);
	//printf("Value at 8,7: %d\n", data.world_map[8][7]);
    a_star(0, 0, 8, 7, &data);
    for (int i = 0; i < data.map_height; i++) {
        free(data.world_map[i]);
    }
    free(data.world_map);
    return (0);
}
