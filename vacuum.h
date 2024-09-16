
#ifndef VACUUM_H
#define VACUUM_H

class Vacuum
{
private:
    int x, y;
    int dirtCapacity;
    int maxCapacity;

public:
    Vacuum(int startX, int startY) : x(startX), y(startY), dirtCapacity(0), maxCapacity(25) {}

    int getX() const { return x; }
    int getY() const { return y; }
    int getDirtCapacity() const { return dirtCapacity; }
    int getMaxCapacity() const { return maxCapacity; }
    void move(int newX, int newY) { x = newX; y = newY; }
    void dump() { dirtCapacity = 0; }

    // Add the collectDirt method
    void collectDirt(int amount);
};

#endif
