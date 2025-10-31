// Simple Maze Solver (BFS) in C
// Equivalent to your Python version

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ROWS 50
#define MAX_COLS 50
#define INF 999999

// ---------- Maze structure ----------
typedef struct {
    int grid[MAX_ROWS][MAX_COLS];
    int rows;
    int cols;
    int start_r, start_c;
    int end_r, end_c;
} Maze;

// ---------- Queue for BFS ----------
typedef struct {
    int r, c;
} Point;

typedef struct {
    Point data[MAX_ROWS * MAX_COLS];
    int front, rear;
} Queue;

void init_queue(Queue* q) { q->front = q->rear = 0; }
bool empty(Queue* q) { return q->front == q->rear; }
void enqueue(Queue* q, int r, int c) { q->data[q->rear++] = (Point){r, c}; }
Point dequeue(Queue* q) { return q->data[q->front++]; }

// ---------- Maze helpers ----------
bool in_bounds(Maze* m, int r, int c) {
    return r >= 0 && c >= 0 && r < m->rows && c < m->cols;
}

bool is_wall(Maze* m, int r, int c) {
    return m->grid[r][c] == 1;
}

void show_maze(Maze* m, bool path[MAX_ROWS][MAX_COLS]) {
    for (int r = 0; r < m->rows; r++) {
        for (int c = 0; c < m->cols; c++) {
            if (r == m->start_r && c == m->start_c) printf("S ");
            else if (r == m->end_r && c == m->end_c) printf("E ");
            else if (is_wall(m, r, c)) printf("# ");
            else if (path[r][c]) printf("* ");
            else printf(". ");
        }
        printf("\n");
    }
}

// ---------- BFS Solver ----------
int solve_bfs(Maze* m, bool path[MAX_ROWS][MAX_COLS]) {
    bool visited[MAX_ROWS][MAX_COLS] = {false};
    Point prev[MAX_ROWS][MAX_COLS];
    Queue q;
    init_queue(&q);

    enqueue(&q, m->start_r, m->start_c);
    visited[m->start_r][m->start_c] = true;

    int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    bool found = false;

    while (!empty(&q)) {
        Point cur = dequeue(&q);
        if (cur.r == m->end_r && cur.c == m->end_c) {
            found = true;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nr = cur.r + dirs[i][0];
            int nc = cur.c + dirs[i][1];
            if (in_bounds(m, nr, nc) && !visited[nr][nc] && !is_wall(m, nr, nc)) {
                visited[nr][nc] = true;
                prev[nr][nc] = cur;
                enqueue(&q, nr, nc);
            }
        }
    }

    if (!found) return INF;

    // reconstruct path
    for (int r = 0; r < m->rows; r++)
        for (int c = 0; c < m->cols; c++)
            path[r][c] = false;

    int dist = 0;
    Point cur = {m->end_r, m->end_c};
    while (!(cur.r == m->start_r && cur.c == m->start_c)) {
        path[cur.r][cur.c] = true;
        Point p = prev[cur.r][cur.c];
        cur = p;
        dist++;
    }
    path[m->start_r][m->start_c] = true;

    return dist;
}

// ---------- Load sample maze ----------
void load_sample_maze(Maze* m) {
    int sample[6][8] = {
        {0,0,0,0,1,0,0,0},
        {1,1,0,1,1,0,1,0},
        {0,0,0,0,0,0,1,0},
        {0,1,1,1,0,1,0,0},
        {0,0,0,1,0,0,0,1},
        {1,1,0,0,0,1,0,0}
    };
    m->rows = 6;
    m->cols = 8;
    for (int r = 0; r < m->rows; r++)
        for (int c = 0; c < m->cols; c++)
            m->grid[r][c] = sample[r][c];

    m->start_r = 0; m->start_c = 0;
    m->end_r = 5;   m->end_c = 7;
}

// ---------- Menu ----------
void menu() {
    printf("\n=== Maze Solver (BFS) ===\n");
    printf("1. Load sample maze\n");
    printf("2. Show maze\n");
    printf("3. Solve (BFS shortest path)\n");
    printf("0. Exit\n");
}

// ---------- Main ----------
int main() {
    Maze maze = {0};
    bool path[MAX_ROWS][MAX_COLS] = {false};
    int choice;

    while (1) {
        menu();
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            load_sample_maze(&maze);
            printf("Sample maze loaded.\n");
        } 
        else if (choice == 2) {
            if (maze.rows == 0) printf("Maze not loaded.\n");
            else show_maze(&maze, path);
        }
        else if (choice == 3) {
            if (maze.rows == 0) {
                printf("Load a maze first.\n");
                continue;
            }
            int dist = solve_bfs(&maze, path);
            if (dist == INF) {
                printf("No path found.\n");
            } else {
                printf("Shortest path length: %d steps\n", dist);
                show_maze(&maze, path);
            }
        } 
        else if (choice == 0) {
            printf("Goodbye!\n");
            break;
        } 
        else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}

