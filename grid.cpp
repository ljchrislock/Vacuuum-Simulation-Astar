
#include "Grid.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Constructor to parse the CSV file and initialize the grid
Grid::Grid(const std::string &filename)
{
    std::ifstream file(filename);
    std::string line;

    // First pass to determine the grid dimensions
    int numRows = 0;
    int numCols = 0;

    while (getline(file, line))
    {
        std::stringstream ss(line);
        std::string cell;
        int colCount = 0;

        while (getline(ss, cell, ','))
        {
            colCount++;
        }

        numCols = std::max(numCols, colCount);
        numRows++;
    }

    // Resize the grid based on determined dimensions
    grid.resize(numRows, std::vector<Cell>(numCols));

    // Rewind the file to the beginning for the second pass
    file.clear();
    file.seekg(0);

    int row = 0;
    while (getline(file, line))
    {
        std::stringstream ss(line);
        std::string cell;
        int col = 0;

        while (getline(ss, cell, ','))
        {
            if (cell[0] == 'D')
            {
                try
                {
                    grid[row][col].dirtAmount = std::stoi(cell.substr(1));
                }
                catch (const std::invalid_argument &e)
                {
                    std::cerr << "Invalid dirt amount in cell: " << cell << " at row: " << row << " col: " << col << std::endl;
                }
            }
            else if (cell[0] == 'V')
            {
                grid[row][col].dirtAmount = 0;
                vacuumStartX = row;
                vacuumStartY = col;
            }
            else if (cell == "O")
            {
                grid[row][col].isObstacle = true;
            }
            else if (cell == "G")
            {
                grid[row][col].isGarbage = true;
            }
            else if (cell == "C")
            {
                grid[row][col].isCat = true;
            }
            col++;
        }
        row++;
    }

    // Debugging: Print the initial grid state to verify correct loading
    std::cout << "Initial Grid State:\n";
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (grid[i][j].isGarbage) std::cout << "G ";
            else if (grid[i][j].isObstacle) std::cout << "O ";
            else if (grid[i][j].isCat) std::cout << "C ";
            else if (i == vacuumStartX && j == vacuumStartY) std::cout << "V ";
            else std::cout << "D" << grid[i][j].dirtAmount << " ";
        }
        std::cout << "\n";
    }
}

// Generate output text file of actions taken instead of CSV
void Grid::generateOutput(const std::string &filename)
{
    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cerr << "Error opening output file.\n";
        return;
    }

    // For demonstration, let's assume we log the grid state and vacuum actions here
    outFile << "Grid Output - Final State and Actions\n";
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            if (grid[i][j].isGarbage) {
                outFile << "Garbage at: (" << i << "," << j << ")\n";
            }
            if (grid[i][j].isObstacle) {
                outFile << "Obstacle at: (" << i << "," << j << ")\n";
            }
            if (grid[i][j].dirtAmount > 0) {
                outFile << "Dirt left at: (" << i << "," << j << ") - Amount: " << grid[i][j].dirtAmount << "\n";
            }
        }
    }

    outFile << "End of output log.\n";
    outFile.close();
}
