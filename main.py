#!/usr/bin/env python3
# Simple Maze Solver (BFS) – clean & minimal

from collections import deque

class Maze:
    def __init__(self):
        # grid: list[list[int]] where 0=path, 1=wall
        self.grid = []
        self.start = (0, 0)  # (row, col)
        self.end = (0, 0)

    # ---------- Helpers ----------
    def in_bounds(self, r, c):
        return 0 <= r < self.rows() and 0 <= c < self.cols()

    def rows(self):
        return len(self.grid)

    def cols(self):
        return len(self.grid[0]) if self.grid else 0

    def is_wall(self, r, c):
        return self.grid[r][c] == 1

    # ---------- View ----------
    def show(self, path=None):
        """
        Print the maze. Optional 'path' is list of (r,c) cells for the shortest path.
        S = start, E = end, # = wall, . = path, * = shortest-path cells
        """
        if not self.grid:
            print("Maze is empty.")
            return

        path_set = set(path or [])
        for r in range(self.rows()):
            row_chars = []
            for c in range(self.cols()):
                if (r, c) == self.start:
                    ch = "S"
                elif (r, c) == self.end:
                    ch = "E"
                elif self.is_wall(r, c):
                    ch = "#"
                elif (r, c) in path_set:
                    ch = "*"
                else:
                    ch = "."
                row_chars.append(ch)
            print(" ".join(row_chars))

    # ---------- Edit ----------
    def toggle_wall(self, r, c):
        if not self.in_bounds(r, c):
            return False
        self.grid[r][c] = 1 - self.grid[r][c]  # flip 0 <-> 1
        return True

    def set_start(self, r, c):
        if not self.in_bounds(r, c) or self.is_wall(r, c):
            return False
        self.start = (r, c)
        return True

    def set_end(self, r, c):
        if not self.in_bounds(r, c) or self.is_wall(r, c):
            return False
        self.end = (r, c)
        return True

    # ---------- BFS Shortest Path ----------
    def solve_bfs(self):
        """
        Returns (path, distance) where path is list[(r,c)] from S to E (inclusive).
        If no path exists, returns ([], inf).
        """
        if not self.grid:
            return [], float('inf')

        sr, sc = self.start
        er, ec = self.end

        q = deque()
        q.append((sr, sc))
        visited = [[False]*self.cols() for _ in range(self.rows())]
        prev = [[None]*self.cols() for _ in range(self.rows())]
        visited[sr][sc] = True

        # 4-directional moves (up, down, left, right)
        dirs = [(-1,0), (1,0), (0,-1), (0,1)]

        while q:
            r, c = q.popleft()
            if (r, c) == (er, ec):
                break  # reached end

            for dr, dc in dirs:
                nr, nc = r + dr, c + dc
                if self.in_bounds(nr, nc) and not visited[nr][nc] and not self.is_wall(nr, nc):
                    visited[nr][nc] = True
                    prev[nr][nc] = (r, c)
                    q.append((nr, nc))

        # reconstruct path
        if not visited[er][ec]:
            return [], float('inf')  # no path

        path = []
        cur = (er, ec)
        while cur is not None:
            path.append(cur)
            pr = prev[cur[0]][cur[1]]
            cur = pr
        path.reverse()
        return path, len(path) - 1  # steps as distance

# ---------- Sample Maze ----------
def load_sample_maze(m: Maze):
    """
    Load a small demo maze (0=path, 1=wall).
    'S' at (0,0), 'E' at (5,7).
    """
    m.grid = [
        [0,0,0,0,1,0,0,0],
        [1,1,0,1,1,0,1,0],
        [0,0,0,0,0,0,1,0],
        [0,1,1,1,0,1,0,0],
        [0,0,0,1,0,0,0,1],
        [1,1,0,0,0,1,0,0],
    ]
    m.set_start(0, 0)
    m.set_end(5, 7)

# ---------- Menu ----------
def menu():
    print("\n=== Maze Solver (BFS) ===")
    print("1. Load sample maze")
    print("2. Show maze")
    print("3. Solve (BFS shortest path)")
    print("4. Toggle wall at (row, col)")
    print("5. Set START (row, col)")
    print("6. Set END (row, col)")
    print("0. Exit")

def ask_int(prompt):
    while True:
        try:
            return int(input(prompt).strip())
        except ValueError:
            print("Enter an integer.")

def main():
    maze = Maze()

    while True:
        menu()
        choice = input("Choose an option: ").strip()

        if choice == "1":
            load_sample_maze(maze)
            print("Sample maze loaded.")

        elif choice == "2":
            maze.show()

        elif choice == "3":
            path, dist = maze.solve_bfs()
            if dist == float('inf'):
                print("No path found.")
                maze.show()
            else:
                print(f"Shortest path length: {dist} steps")
                maze.show(path=path)

        elif choice == "4":
            if not maze.grid:
                print("Load a maze first.")
                continue
            r = ask_int("Row: ")
            c = ask_int("Col: ")
            if maze.toggle_wall(r, c):
                print("Toggled.")
            else:
                print("Out of bounds.")
            maze.show()

        elif choice == "5":
            if not maze.grid:
                print("Load a maze first.")
                continue
            r = ask_int("Start row: ")
            c = ask_int("Start col: ")
            print("Set." if maze.set_start(r, c) else "Invalid (wall/out of bounds).")
            maze.show()

        elif choice == "6":
            if not maze.grid:
                print("Load a maze first.")
                continue
            r = ask_int("End row: ")
            c = ask_int("End col: ")
            print("Set." if maze.set_end(r, c) else "Invalid (wall/out of bounds).")
            maze.show()

        elif choice == "0":
            print("Goodbye!")
            break

        else:
            print("Invalid choice.")

if __name__ == "__main__":
    main()
