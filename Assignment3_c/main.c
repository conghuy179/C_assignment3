#include <stdio.h>
#include <stdbool.h>

#define NUM_ROWS 9
#define NUM_COLS 9
#define SIZE 81
#define MAX_PATH_LENGTH 18
#define MAX_NEIGHBORS 4

typedef struct POINT
{
    int row;
    int col;
    int value;

    // mark point as visited or not
    bool visited;

    struct POINT *prev;
} point_t;

typedef struct QUEUE
{
    point_t *items[SIZE];
    int rear;
    int front;
} queue_t;

bool is_empty(queue_t *q)
{
    return q->front == -1;
}

bool is_full(queue_t *q)
{
    return q->rear == SIZE - 1;
}

void print_point(point_t *p)
{
    printf("Point[row=%d,col=%d,value=%d,visited=%s,prev=%p]\n",
           p->row, p->col, p->value, p->visited ? "true" : "false", p->prev);
}

void print_queue(queue_t *q)
{
    if (!is_empty(q))
    {
        printf("queue [front=%d, rear=%d, items=[", q->front, q->rear);
        for (int i = q->front; i <= q->rear; i++)
        {
            print_point(q->items[i]);
            if (i != q->rear)
            {
                printf(", ");
            }
        }
        printf("]]\n");
    }
    else
    {
        printf("the queue is empty [front=%d, rear=%d].\n", q->front, q->rear);
    }
}

void enqueue(queue_t *q, point_t *point_ptr)
{
    if (!is_full(q))
    {
        if (q->front == -1)
        {
            q->front = 0;
        }
        q->rear++;
        q->items[q->rear] = point_ptr;

        printf("DEBUG: enqueue: inserted to pos. %d in queue: ", q->rear + 1);
        print_point(point_ptr);
    }
    else
    {
        printf("DEBUG: enqueue: queue is full.\n");
        print_queue(q);
    }
}

point_t *dequeue(queue_t *q)
{
    if (is_empty(q))
    {
        printf("DEBUG: dequeue: queue is empty.\n");
        return NULL;
    }
    else
    {
        point_t *elem = q->items[q->front];
        q->front++;
        if (q->front > q->rear)
        {
            q->front = -1;
            q->rear = -1;
        }
        return elem;
    }
}

void init_queue(queue_t *q)
{
    q->rear = -1;
    q->front = -1;
}

/*
Ma tran bieu dien ban do
*/
point_t matrix[NUM_ROWS][NUM_COLS];

bool is_valid(int row, int col)
{
    return (row >= 0) && (row < NUM_ROWS) && (col >= 0) && (col < NUM_COLS);
}

void find_neighbors(int row, int col, point_t *out_neighbors[4], int *out_count)
{
    int count = 0;

    printf("DEBUG: row = %d, col = %d\n", row, col);

    // ben phai
    if (is_valid(row, col + 1))
    {
        printf("DEBUG: row = %d, col = %d, val = %d\n", row, col + 1, matrix[row][col + 1].value);
        if (matrix[row][col + 1].value == 1)
        {
            out_neighbors[count] = &matrix[row][col + 1];
            count++;
        }
    }

    // ben trai
    if (is_valid(row, col - 1))
    {
        printf("DEBUG: row = %d, col = %d, val = %d\n", row, col - 1, matrix[row][col - 1].value);
        if (matrix[row][col - 1].value == 1)
        {
            out_neighbors[count] = &matrix[row][col - 1];
            count++;
        }
    }

    // ben tren
    if (is_valid(row - 1, col))
    {
        printf("DEBUG: row = %d, col = %d, val = %d\n", row - 1, col, matrix[row - 1][col].value);
        if (matrix[row - 1][col].value == 1)
        {
            out_neighbors[count] = &matrix[row - 1][col];
            count++;
        }
    }

    // ben duoi
    if (is_valid(row + 1, col))
    {
        printf("DEBUG: row = %d, col = %d, val = %d\n", row + 1, col, matrix[row + 1][col].value);
        if (matrix[row + 1][col].value == 1)
        {
            out_neighbors[count] = &matrix[row + 1][col];
            count++;
        }
    }

    *out_count = count;
}

void find_shortest_path(int dst_row, int dst_col)
{

    queue_t q;
    init_queue(&q);

    bool found = false;
    point_t *found_ptr = NULL;

    point_t *neighbors[MAX_NEIGHBORS];
    int neighbor_count = 0;

    enqueue(&q, &matrix[0][0]);
    matrix[0][0].visited = true;

    while (!is_empty(&q) && !found)
    {
        point_t *p = dequeue(&q);

        find_neighbors(p->row, p->col, neighbors, &neighbor_count);

        for (int i = 0; i < neighbor_count; i++)
        {
            if (!neighbors[i]->visited)
            {
                neighbors[i]->visited = true;
                neighbors[i]->prev = p;

                if (neighbors[i]->row == dst_row && neighbors[i]->col == dst_col)
                {
                    found = true;
                    found_ptr = neighbors[i];
                    break;
                }
                else
                {
                    enqueue(&q, neighbors[i]);
                }
            }
        }
    }

    if (found)
    {
        int len = 0;
        point_t *path[MAX_PATH_LENGTH];

        while (found_ptr != NULL)
        {
            path[len] = found_ptr;
            len++;
            found_ptr = found_ptr->prev;
        }

        printf("Duong di ngan nha tu O(0, 0) den A(%d, %d) co do dai la %d o:\n",
               dst_row, dst_col, len);
        for (int k = len - 1; k >= 0; k--)
        {
            printf("(%d, %d)", path[k]->row, path[k]->col);
            if (k != 0)
            {
                printf(" -> ");
            }
        }
        printf("\n");
    }
    else
    {
        printf("Khong co duong di tu O(0, 0) den A(%d, %d).\n", dst_row, dst_col);
    }
}

int main()
{

    printf("CHUONG TRINH TIM DUONG DI NGAN NHAT TU O(0, 0) DEN A(dong, cot):\n\n");

    int values[NUM_ROWS][NUM_COLS] =
        {
            {1, 0, 0, 0, 1, 0, 1, 1, 0},
            {1, 1, 0, 1, 1, 1, 0, 0, 1},
            {0, 1, 0, 1, 1, 0, 1, 0, 1},
            {0, 1, 1, 0, 0, 1, 0, 1, 1},
            {0, 0, 1, 0, 1, 0, 1, 0, 0},
            {1, 1, 1, 0, 0, 0, 0, 1, 1},
            {1, 0, 1, 1, 1, 1, 1, 0, 0},
            {1, 1, 1, 0, 0, 0, 1, 0, 1},
            {0, 0, 0, 1, 1, 1, 1, 1, 0}};

    printf("Ma tran 9x9 bieu dien cho mat phang 2 chieu:\n");
    for (int r = 0; r < NUM_ROWS; r++)
    {
        for (int c = 0; c < NUM_COLS; c++)
        {
            matrix[r][c] = (point_t){.row = r, .col = c, .visited = false, .value = values[r][c], .prev = NULL};
            printf("%d ", matrix[r][c].value);
        }
        printf("\n");
    }

    printf("\nToa do o xuat phat lat O(0, 0).\n");

    int row = 0;
    int col = 0;
    bool is_input_ok = false;
    do
    {
        printf("\nHay nhap toa do cua o dich den A:\n");

        printf("Nhap dong: \n");
        scanf("%d", &row);

        printf("Nhap cot: \n");
        scanf("%d", &col);

        is_input_ok = is_valid(row, col);

        if (!is_input_ok)
        {
            printf("Gia tri cua dong phai tu 0 den 8!\n");
            printf("Gia tri cua cot  phai tu 0 den 8!\n");
        }

    } while (!is_input_ok);

    find_shortest_path(row, col);

    return 0;
}
