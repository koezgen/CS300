#ifndef _MAZEWALLS_H
#define _MAZEWALLS_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class mazeWalls
{
    private:
        int l;
        int r;
        int u;
        int d;

    public:
        // Constructors and Destructors
        mazeWalls();
        mazeWalls(int l, int r, int u, int d);
        ~mazeWalls();

        // Getters
        int getL();
        int getR();
        int getU();
        int getD();

        // Setters
        void setL(int l);
        void setR(int r);
        void setU(int u);
        void setD(int d);
    
    // This function must be a friend function because it accesses private data parts. 
    friend ostream & operator<<(ostream &out, const mazeWalls &walls);
    friend class mazeBlock;
};

#include "mazeWalls.hpp"

#endif