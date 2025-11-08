// main.c
// Maze solver: BFS + random/sample maze + path display
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX 100

typedef struct {
    int grid[MAX][MAX];
    int rows, cols;
    int start_r, start_c;
    int end_r, end_c;
    bool loaded;
} Maze;

typedef struct {
    int r, c;
    int dist;
} Node;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

// ---------- Load a simple sample maze ----------
void load_sample_maze(Maze *m) {
    int data[5][5] = {
        {0,0,0,0,1},
        {1,1,0,1,0},
        {0,0,0,0,0},
        {0,1,1,1,0},
        {0,0,0,0,0}
    };

    m->rows = 5;
    m->cols = 5;

    for (int r = 0; r < m->rows; r++)
        for (int c = 0; c < m->cols; c++)
            m->grid[r][c] = data[r][c];

    m->start_r = 0;
    m->start_c = 0;
    m->end_r = 4;
    m->end_c = 4;
    m->loaded = true;
}

// ---------- Generate Random Maze ----------
void generate_random_maze(Maze *m, int rows, int cols) {
    m->rows = rows;
    m->cols = cols;
    srand((unsigned)time(NULL));

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            m->grid[r][c] = (rand() % 100 < 30) ? 1 : 0; // ~25% walls
        }
    }

    m->start_r = 0; m->start_c = 0;
    m->end_r = rows - 1; m->end_c = cols - 1;
    m->grid[m->start_r][m->start_c] = 0;
    m->grid[m->end_r][m->end_c] = 0;
    m->loaded = true;
}

// ---------- Show Maze (optionally with path) ----------
void show_maze(Maze *m, bool path[MAX][MAX]) {
    if (!m->loaded) { printf("No maze loaded.\n"); return; }
    printf("\nMaze (%dx%d):\n", m->rows, m->cols);
    for (int r = 0; r < m->rows; r++) {
        for (int c = 0; c < m->cols; c++) {
            if (r == m->start_r && c == m->start_c) printf("S ");
            else if (r == m->end_r && c == m->end_c) printf("E ");
            else if (path != NULL && path[r][c]) printf("* ");
            else if (m->grid[r][c] == 1) printf("# ");
            else printf(". ");
        }
        printf("\n");
    }
}

// ---------- BFS Solver with path reconstruction ----------
void solve_bfs(Maze *m) {
    if (!m->loaded) { printf("Load or generate a maze first.\n"); return; }

    bool visited[MAX][MAX] = {false};
    int prev_r[MAX][MAX], prev_c[MAX][MAX];
    for (int i=0;i<m->rows;i++) for (int j=0;j<m->cols;j++){ prev_r[i][j] = prev_c[i][j] = -1; }

    Node queue[MAX * MAX];
    int front = 0, rear = 0;

    queue[rear++] = (Node){m->start_r, m->start_c, 0};
    visited[m->start_r][m->start_c] = true;

    bool found = false;
    while (front < rear) {
        Node cur = queue[front++];
        if (cur.r == m->end_r && cur.c == m->end_c) {
            // reconstruct path
            bool path[MAX][MAX] = {false};
            int cr = cur.r, cc = cur.c;
            while (!(cr == m->start_r && cc == m->start_c)) {
                path[cr][cc] = true;
                int pr = prev_r[cr][cc];
                int pc = prev_c[cr][cc];
                cr = pr; cc = pc;
            }
            path[m->start_r][m->start_c] = true;
            printf("Shortest path length: %d steps.\n", cur.dist);
            show_maze(m, path);
            found = true;
            break;
        }

        for (int k = 0; k < 4; k++) {
            int nr = cur.r + dr[k];
            int nc = cur.c + dc[k];
            if (nr >= 0 && nr < m->rows && nc >= 0 && nc < m->cols &&
                !visited[nr][nc] && m->grid[nr][nc] == 0) {
                visited[nr][nc] = true;
                prev_r[nr][nc] = cur.r;
                prev_c[nr][nc] = cur.c;
                queue[rear++] = (Node){nr, nc, cur.dist + 1};
            }
        }
    }

    if (!found) {
        printf("No path found!\n");
        show_maze(m, NULL);
    }
}

int main(void) {
    Maze maze; maze.loaded = false;

    while (1) {
        printf("\n==== Maze Solver ====\n");
        printf("1. Load sample maze\n");
        printf("2. Generate random maze\n");
        printf("3. Show maze\n");
        printf("4. Solve using BFS (show path)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        int choice;
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // flush
            printf("Invalid input. Try again.\n");
            continue;
        }

        if (choice == 1) {
            load_sample_maze(&maze);
            printf("Sample maze loaded.\n");
        } else if (choice == 2) {
            int r, c;
            printf("Enter number of rows: "); scanf("%d", &r);
            printf("Enter number of columns: "); scanf("%d", &c);
            generate_random_maze(&maze, r, c);
            printf("Random maze (%dx%d) generated!\n", r, c);
        } else if (choice == 3) {
            show_maze(&maze, NULL);
        } else if (choice == 4) {
            solve_bfs(&maze);
        } else if (choice == 5) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

