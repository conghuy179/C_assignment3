#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_ROWS 9
#define NUM_COLS 9
#define SIZE 81
#define MAX_PATH_LENGTH 18
#define MAX_NEIGHBORS 4

/*
Cau truc cua 1 nut trong ma tran (point):
Bao gom:
1. Toa do x cua nut
2. Toa do y cua nut
3. Gia tri (0 hoac 1) cua nut
4. Danh dau nut da duoc di qua hay chua
5. Con tro tro den nut lien truoc do truoc khi di
den nut nay.
Muc dich:
Tao cau truc 1 nut
*/
typedef struct POINT
{
    int row;
    int column;
    int value;
    bool visited;
    POINT *prev;
} point_t;

/*
Cau truc hang doi (queue):
Bao gom:
1. Chi so dau cua hang doi
2. Chi so cuoi cua hang doi
3. Luu tru cac nut
Muc dich: Tao 1 cau truc hang doi de luu tru cac nut dang
doi xu ly
*/
typedef struct QUEUE
{
    int front;
    int rear;
    point_t *items[SIZE];
} queue_t;

/*
Ham khoi tao queue:
Muc dich: Khoi tao hang doi queue
*/
void init_queue(queue_t *q)
{
    q->front = -1;
    q->rear = -1;
}
/*
Ham is_empty: La hang doi rong
Muc dich: Kiem tra xem co phan tu nao trong queue hay khong
*/
bool is_empty(queue_t *q)
{
    return q->front == -1;
}

/*
Ham is_full: Hang doi day
Muc dich: Kiem tra xem queue da day phan tu hay chua
*/
bool is_full(queue_t *q)
{
    return q->rear == SIZE - 1;
}

/*
Ham in nut:
Muc dich: In thong tin cua nut
*/
void print_point (point_t *p)
{
    printf("Point[row = %d, col = %d, value = %d, visited = %s, prev = %p]\n",
           p->row, p->column, p->value, p->visited ? "true" : "false", p->prev);
}

/*Ham in queue:
Muc dich: In thong tin cua hang doi queue
*/
void print_queue (queue_t *q)
{
    if (!is_empty(q))
    {
        printf("Queue [front = %d, rear = %d, items = [", q->front, q->rear);
        for (int i = q->front, i<= q->rear; i++)
        {
            print_point(q->items[i]);
            if (i != q->rear)
            {
                printf(" , ");
            }
        }
        printf("]].\n");
    }
    else
    {
        printf("The queue is empty [front = %d, rear = %d].\n", q->front, q->rear);
    }
}

/*
Ham Enqueue:
Muc dich: Bo sung them nut vao queue
*/
void enqueue (queue_t *q, point_t *q)
{
    if (!is_full(q))
    {
        if (!is_empty(q))
        {
            q->front = 0;
        }
        q->rear++;
        q->items[q->rear] = q;

        printf("DEBUG: enqueue: inserted to pos. %d in queue: ", q->rear +1);
        print_point(q);
    }
    else
    {
        printf("The queue is full.\n");
        print_queue(q);
    }
}

/*
Ham Dequeue:
Muc dich: Loai bo nut dung dau trong queue.
*/
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

/*
Ma tran bieu dien ban do
Muc dich: Bieu dien tap hop cac diem tao thanh ban do
*/
point_t matrix[NUM_ROWS][NUM_COLS];

/*
Ham is_valid
Muc dich: Kiem tra so nhap vao co thuoc trong ban do hay khong
*/

bool is_valid(int row, int col)
{
    return (row >= 0) && (col >= 0) && (row <= NUM_ROWS) && (col <= NUM_COLS);
}

/*
Ham find_neighbors
Muc dich: Xac dinh 4 points xung quanh xem co the di qua duoc
hay khong
*/
void find_neighbors (int row, int col, point_t *out_neighbors[4], int *out_count)
{
     int count = 0;
     printf("DEBUG: row = %d, col = %d\n", row, col);

     //ben phai
     if (is_valid(row, col + 1))
     {
         printf("DEBUG: row = %d, col = %d\n", row, col + 1);
         if (matrix[row][col + 1] == 1)
         {
            out_neighbors[count] = &matrix[row][col + 1];
            count++;
         }
     }

     // ben trai
     if (is_valid(row, col -1))
     {
         printf("DEBUG: row = %d, col = %d\n", row, col - 1);
         if (matrix[row][col - 1] == 1)
         {
            out_neighbors[count] = &matrix[row][col - 1];
            count++;
         }
     }

     // ben tren
     if (is_valid(row - 1, col))
     {
         printf("DEBUG: row = %d, col = %d\n", row - 1, col);
         if (matrix[row - 1][col] == 1)
         {
            out_neighbors[count] = &matrix[row - 1][col];
            count++;
         }
     }

     // ben duoi
     if (is_valid(row + 1, col))
     {
         printf("DEBUG: row = %d, col = %d\n", row + 1, col);
         if (matrix[row + 1][col] == 1)
         {
            out_neighbors[count] = &matrix[row + 1][col];
            count++;
         }
     }
     *out_count = count;
}

/*
Ham find_shortest_path
Muc dich: tim kiem duong di ngan nhat tu diem khoi dau den
diem mong muon
*/

void find_shortest_path(int dst_row, int dst_col)
{
    queue_t q;
    init_queue(&q);

    bool found = false;
    point_t *found_ptr = NULL;

    point_t *neighbors[MAX_NEIGHBORS];
    int neighbor_count = 0;

    enqueue(&q,&matrix[0][0]);
    //TODO: Continue and read carefully
}

int main()
{
    printf("Hello world!\n");
    return 0;
}
