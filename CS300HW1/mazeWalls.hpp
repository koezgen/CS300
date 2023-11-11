#include "mazeWalls.h"
// Console Stream Overload
ostream & operator<<(ostream &out, const mazeWalls &walls)
{
    out << "l=" << walls.l << " " << "r=" << walls.r << " " << "u=" << walls.u << " " << "d=" << walls.d << endl;
    return out;
}

mazeWalls::mazeWalls()
{
    l = 1;
    r = 1;
    u = 1;
    d = 1;
}

mazeWalls::mazeWalls(int l, int r, int u, int d)
{
    this->l = l;
    this->r = r;
    this->u = u;
    this->d = d;
}

mazeWalls::~mazeWalls()
{
    // Nothing to do here
}

int mazeWalls::getL()
{
    return l;
}

int mazeWalls::getR()
{
    return r;
}

int mazeWalls::getU()
{
    return u;
}

int mazeWalls::getD()
{
    return d;
}

void mazeWalls::setL(int l)
{
    this->l = l;
}

void mazeWalls::setR(int r)
{
    this->r = r;
}

void mazeWalls::setU(int u)
{
    this->u = u;
}

void mazeWalls::setD(int d)
{
    this->d = d;
}