# 🧩 Maze Solver (BFS)

A **Python-based console application** that finds the **shortest path through a maze** using **Breadth-First Search (BFS)**.
This tool lets you load, edit, and visualize a maze grid, then solve it step-by-step with the shortest route highlighted.

---

## 🚀 Features

* 🧱 Load or create a custom maze grid
* 🔁 Toggle walls interactively
* 🟢 Set custom start and end points
* 🔍 Solve using **BFS shortest path algorithm**
* 🧭 Visualize the maze with the path displayed in the console
* 🎯 Includes a ready-to-use sample maze

---

## 🧩 Maze Representation

* `0` → open path
* `1` → wall
* `S` → start cell
* `E` → end cell
* `*` → shortest path (computed)
* `.` → empty traversable space
* `#` → wall

Example (solved view):

```
S . . . # . . .
# # . # # . # .
. . . . . . # .
. # # # . # . .
. . . # . . . #
# # . . . # . E
```

---

## ⚙️ Installation & Usage

### 1️⃣ Clone the Repository

```bash
git clone https://github.com/ombansal1/MazeSolver.git
cd MazeSolver
```

### 2️⃣ Run the App

```bash
python3 main.py
```

---

## 🧮 Menu Options

```
=== Maze Solver (BFS) ===
1. Load sample maze
2. Show maze
3. Solve (BFS shortest path)
4. Toggle wall at (row, col)
5. Set START (row, col)
6. Set END (row, col)
0. Exit
```

---

## 🧭 Example Run

```
=== Maze Solver (BFS) ===
Choose an option: 1
Sample maze loaded.

Choose an option: 3
Shortest path length: 14 steps
S * * * # . . .
# # * # # . # .
. . * * * * # .
. # # # * # . .
. . . # * * * #
# # . . . # . E
```

---

## 🧠 How It Works

* Uses **Breadth-First Search (BFS)** to explore all paths in layers until it reaches the goal.
* Guarantees the **shortest path** in an unweighted grid (each move = 1 step).
* Supports **4-directional movement** (up, down, left, right).

---

## 🧱 File Structure

```
MazeSolver/
│
├── maze_solver.py   # Main program
├── README.md        # Project documentation
```

---

## 🧑‍💻 Tech Stack

* **Language:** Python 3
* **Algorithm:** Breadth-First Search (BFS)
* **Libraries:** `collections.deque` (for queue-based BFS)

---

## 💡 Future Enhancements

* 🧮 Add **A*** (A-star) algorithm for weighted mazes
* 🎨 GUI version using Tkinter or Pygame
* 🗺️ Load maze from text or image file
* 🌀 Add diagonal movement options

---

## 👨‍💻 Author

**Om Bansal**
📧 [[ombansal2109@gmail.com](mailto:ombansal2109@gmail.com)]
🐙 [GitHub Profile](https://github.com/ombansal1)

---
