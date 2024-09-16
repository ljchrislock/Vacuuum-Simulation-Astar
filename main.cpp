#include "Grid.h"
#include "Vacuum.h"
#include "AStar.h"

int main()
{
    // Parse the input CSV and setup the grid
    Grid grid("input_test_2.csv");

    // Initialize the vacuum at the starting position
    Vacuum vacuum(grid.getVacuumStartX(), grid.getVacuumStartY());

    // Call A* search to clean the room
    aStarSearch(vacuum, grid);

    // Generate output log of actions
    grid.generateOutput("output.csv");

    return 0;
}
