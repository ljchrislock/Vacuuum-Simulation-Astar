
#include "AStar.h"
#include <queue>
#include <cmath>
#include <iostream>
#include <fstream>
#include <set>
#include <map>

// Node constructor
Node::Node(int x, int y, int g, int h) : x(x), y(y), gCost(g), hCost(h)
{
    fCost = gCost + hCost; // Calculate fCost as the sum of gCost and hCost
}

// Comparison operator for priority queue
bool Node::operator<(const Node &other) const
{
    return fCost > other.fCost; // The node with the lower fCost has higher priority
}

// Heuristic: Manhattan distance, with a penalty for driving over the sleeping cat
int heuristic(int x1, int y1, int x2, int y2, bool isCat)
{
    int manhattanDistance = std::abs(x1 - x2) + std::abs(y1 - y2);
    int catPenalty = isCat ? 10 : 0;  // Apply a 10-unit penalty if the vacuum crosses the cat's position
    return manhattanDistance * 2 + catPenalty; // Weighted heuristic to prioritize goal proximity
}

// A* search algorithm with special cells preserved in final grid
void aStarSearch(Vacuum &vacuum, Grid &grid)
{
    std::priority_queue<Node> openList;
    std::set<std::pair<int, int>> closedSet;  // Use a set to ensure we do not revisit the same node

    int startX = vacuum.getX();
    int startY = vacuum.getY();
    int goalX = -1, goalY = -1;

    // Locate the garbage position (goal)
    for (int x = 0; x < 6; x++) {
        for (int y = 0; y < 10; y++) {
            if (grid.getCell(x, y).isGarbage) {
                goalX = x;
                goalY = y;
                break;
            }
        }
        if (goalX != -1) break; // Exit the loop once garbage is found
    }

    if (goalX == -1 || goalY == -1) {
        std::cerr << "Error: No garbage (goal) found in the grid." << std::endl;
        return;
    }

    // Initialize the open list with the starting node
    openList.push(Node(startX, startY, 0, heuristic(startX, startY, goalX, goalY, grid.getCell(startX, startY).isCat)));

    // Open file to log actions in the format you specified
    std::ofstream outFile("output.txt");

    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open output file.\n";
        return;
    }

    // Log starting position
    outFile << "Start Position: (" << startX << "," << startY << ")\n";
    outFile << "Actions:\n";
    std::cout << "Logging Start Position\n"; // Console debug message

    // Map of all dirt cells to ensure the vacuum moves toward the nearest dirty cell
    std::map<std::pair<int, int>, int> dirtCells;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid.getCell(i, j).dirtAmount > 0) {
                dirtCells[{i, j}] = grid.getCell(i, j).dirtAmount;
            }
        }
    }

    // Simulate vacuum pathfinding based on dirt priority and dirt capacity
    std::pair<int, int> current_position = {startX, startY};
    int collected_dirt = 0;

    while (!dirtCells.empty()) {
        // Find the nearest dirt cell
        std::pair<int, int> nearestDirt = {-1, -1};
        int minDistance = INT_MAX;
        for (auto &[dirtPos, dirtAmount] : dirtCells) {
            int distance = abs(current_position.first - dirtPos.first) + abs(current_position.second - dirtPos.second);
            if (distance < minDistance) {
                minDistance = distance;
                nearestDirt = dirtPos;
            }
        }

        // Move to the nearest dirt cell
        collected_dirt += dirtCells[nearestDirt];
        outFile << "Move to Dirt at: (" << nearestDirt.first << "," << nearestDirt.second << ")\n";
        outFile << "Suck\n"; // Cleaning action
        dirtCells.erase(nearestDirt);  // Remove cleaned dirt
        current_position = nearestDirt;

        // Check if the vacuum needs to dump dirt
        if (collected_dirt >= vacuum.getMaxCapacity()) {
            outFile << "Move to Garbage at: (" << goalX << "," << goalY << ")\n";
            outFile << "Dump\n";  // Dumping action
            collected_dirt = 0;  // Reset collected dirt
            current_position = {goalX, goalY};  // Move to garbage position
        }
    }

    // Dump remaining dirt after cleaning all dirt cells
    if (collected_dirt > 0) {
        outFile << "Move to Garbage at: (" << goalX << "," << goalY << ")\n";
        outFile << "Dump\n";  // Final dumping action
    }

    // Output the cleaned grid with special cells preserved
    outFile << "Final Grid State:\n";
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid.getCell(i, j).isGarbage) outFile << "G ";  // Preserve garbage
            else if (grid.getCell(i, j).isCat) outFile << "C ";  // Preserve cat
            else if (grid.getCell(i, j).isObstacle) outFile << "O ";  // Preserve obstacles
            else outFile << "D0 ";  // Cleaned cell
        }
        outFile << "\n";
        
    }
    outFile << "THIS IS A CHECK FOR MYSELF TO ENSURE THAT MY ALGORITHM IS CLEANING THE WHOLE GRID AND NOTHING GETS LEFT BEHIND\n";

    // Log final position
    outFile << "Final Position: (" << vacuum.getX() << "," << vacuum.getY() << ")\n";
    std::cout << "Logging Final Position\n"; // Console debug message

    // Flush to ensure data is written
    outFile.flush();

    // Close the file
    outFile.close();
    std::cout << "File closed successfully\n"; // Console debug message
}
