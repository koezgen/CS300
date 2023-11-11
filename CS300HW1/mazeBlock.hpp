#include "mazeBlock.h"

// Console Stream Overload
ostream & operator<<(ostream &out, const mazeBlock &block)
{
    out << "x=" << block.col << " " << "y=" << block.row << " " << block.walls;
    return out;
}

mazeBlock::mazeBlock()
    : row(0), col(0), walls()
{
    row = 0;
    col = 0;
}

mazeBlock::mazeBlock(int row, int col)
    : row(row), col(col), walls()
{
    this->row = row;
    this->col = col;
}

mazeBlock::mazeBlock(int row, int col, int l, int r, int u, int d)
{
    this->row = row;
    this->col = col;
    walls.setL(l);
    walls.setR(r);
    walls.setU(u);
    walls.setD(d);
}

mazeBlock::~mazeBlock()
{
    // Nothing to do here
}

int mazeBlock::getRow()
{
    return row;
}

int mazeBlock::getCol()
{
    return col;
}

bool mazeBlock::getVisit()
{
    return visit;
}

void mazeBlock::setWalls(int l, int r, int u, int d)
{
    walls.setL(l);
    walls.setR(r);
    walls.setU(u);
    walls.setD(d);
}

void mazeBlock::visitBlock()
{
    visit = true;
}

void mazeBlock::breakWall(int direction)
{
    if (direction == 0) walls.setL(0);
    else if (direction == 1) walls.setR(0);
    else if (direction == 2) walls.setU(0);
    else if (direction == 3) walls.setD(0);
}

void mazeBlock::setWall(int direction)
{
    if (direction == 0) walls.setL(1);
    else if (direction == 1) walls.setR(1);
    else if (direction == 2) walls.setU(1);
    else if (direction == 3) walls.setD(1);
}

int* mazeBlock::getWall()
{
    int arr[4];

    arr[0] = walls.getL();
    arr[1] = walls.getR();
    arr[2] = walls.getU();
    arr[3] = walls.getD();

    return arr;
}