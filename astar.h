#ifndef ASTAR_H
#define ASTAR_H

#include "Grid.h"
#include "Vacuum.h"

struct Node
{
    int x, y;
    int gCost;
    int hCost;
    int fCost;

    Node(int x, int y, int g, int h);
    bool operator<(const Node &other) const;
};

// Declare the heuristic function here
int heuristic(int x1, int y1, int x2, int y2);

void aStarSearch(Vacuum &vacuum, Grid &grid);

#endif
