#ifndef _MAZEBLOCK_H
#define _MAZEBLOCK_H

#include <iostream>
#include <string>
#include <fstream>
#include "mazeWalls.h"
using namespace std;

class mazeBlock
{
    private:
        int row;
        int col;
        mazeWalls walls;
        bool visit = false;

    public:
        // Constructors
        mazeBlock();
        mazeBlock(int row, int col);
        mazeBlock(int row, int col, int l, int r, int u, int d);
        ~mazeBlock();

        // Getters
        int getRow();
        int getCol();
        bool getVisit();

        // Setters
        void setWalls(int l, int r, int u, int d);
        void visitBlock();
        void breakWall(int direction);
        void setWall(int direction);
        int* getWall();

    friend class mazeWalls;
    friend ostream & operator<<(ostream &out, const mazeBlock &block);
};


#include "mazeBlock.hpp"

#endif