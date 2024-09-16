#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>

struct Cell
{
    int dirtAmount;
    bool isObstacle;
    bool isGarbage;
    bool isCat;

    Cell() : dirtAmount(0), isObstacle(false), isGarbage(false), isCat(false) {}
};

class Grid
{
private:
    std::vector<std::vector<Cell>> grid;
    int vacuumStartX, vacuumStartY;

public:
    Grid(const std::string &filename); // Constructor to parse CSV
    int getVacuumStartX() const { return vacuumStartX; }
    int getVacuumStartY() const { return vacuumStartY; }

    // Accessor to get a cell at specific coordinates
    Cell &getCell(int x, int y) { return grid[x][y]; }

    void generateOutput(const std::string &filename);
};

#endif
