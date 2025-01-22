
# Vacuum Simulation with A* Pathfinding

## Overview

This project simulates a vacuum robot navigating a grid environment using the A* (A-Star) pathfinding algorithm. It demonstrates how the A* algorithm optimizes pathfinding to clean all designated dirty tiles efficiently.

Key features include:
- Dynamic grid-based environment.
- CSV input for initial grid configuration.
- CSV output showing results after simulation.

---

## File Structure

### Source Code
- **`main.cpp`**: Entry point of the program.
- **`astar.cpp` & `astar.h`**: Implementation of the A* algorithm.
- **`grid.cpp` & `grid.h`**: Defines the grid environment.
- **`vacuum.cpp` & `vacuum.h`**: Vacuum simulation logic.

### Supporting Files
- **`Makefile`**: Automates the build process.
- **Input Files**:
  - `input_test_1.csv`
  - `input_test_2.csv`
- **Output Files**:
  - `output.csv`: Final grid state after the vacuum simulation.
  - `output.txt`: Log of simulation steps.

### Compiled Files
- Precompiled binaries like `main.exe` and object files (e.g., `AStar.o`, `Grid.o`).

---

## Setup and Compilation

### Prerequisites
- A C++ compiler (e.g., `g++`).
- A terminal or command prompt with `make` installed.

### Steps
1. Navigate to the project directory.
2. Run the following command to compile the project:
   ```bash
   make
   ```
3. Execute the program:
   ```bash
   ./vacuum_simulation.exe
   ```

---

## Input Format

The input files (`input_test_1.csv`, `input_test_2.csv`) define the grid environment. Each cell in the CSV represents:
- **`0`**: Clean tile.
- **`1`**: Dirty tile.
- **`2`**: Vacuum's starting position.

---

## Output

### CSV Output
- **`output.csv`**: Final grid state showing cleaned tiles.

### Log
- **`output.txt`**: Detailed step-by-step process of the vacuum's navigation.

---

## Contribution

Feel free to fork this repository and propose improvements or report issues.
