#include <random>
#include <iostream>
#include "mazeStack.h"
#include "mazeBlock.h"
#include "mazeWalls.h"
#include <string>
#include <vector>
#include <fstream>
#include "LinkedList.h"
using namespace std;

/////////////////////////////////////
// Maze Generator and Solver Program
// Written by:
// Kanat Ozgen
// 09.11.2023
// 
// *** Check line 438 for the explanation of the algorithm.
/////////////////////////////////////

/// <summary>
/// Pseudo-random index generator using Mersenne Twister
/// </summary>
/// <param name="max">Maximum number that the index can get</param>
/// <returns>Returns the random index</returns>
int random_int_generator(int max)
{
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0, max);
    auto random_integer = uni(rng);

    return random_integer;
}

/// <summary>
/// Dead-end status checker for maze generation algorithm.
/// </summary>
/// <param name="addr">Address of the current iterator point</param>
/// <param name="maze">Maze matrix</param>
/// <param name="row">Row size of the maze matrix</param>
/// <param name="col">Column size of the maze matrix</param>
/// <returns></returns>
bool dead_end_status(mazeBlock * addr, vector<vector<mazeBlock>>& maze, int row, int col)
{
    linkedList<int> available_directions(3);
    
    // Left - 0
    if (addr->getCol() - 1 < 0)
    {
        available_directions.removeElement(0);
    }
    else if (maze[addr->getRow()][addr->getCol() - 1].getVisit())
    {
        available_directions.removeElement(0);
    }

    // Right - 1
    if (addr->getCol() + 1 > col - 1)
    {
        available_directions.removeElement(1);
    }
    else if (maze[addr->getRow()][addr->getCol() + 1].getVisit())
    {
        available_directions.removeElement(1);
    }

    // Up - 2
    if (addr->getRow() + 1 > row - 1)
    {
        available_directions.removeElement(2);
    }
    else if (maze[addr->getRow() + 1][addr->getCol()].getVisit())
    {
        available_directions.removeElement(2);
    }

    // Down - 3
    if (addr->getRow() - 1 < 0)
    {
        available_directions.removeElement(3);
    }
    else if (maze[addr->getRow() - 1][addr->getCol()].getVisit())
    {
        available_directions.removeElement(3);
    }

    if (available_directions.getSize() == 0)
    {
        return true;
    }

    else
    {
        return false;
    }
}

/// <summary>
/// Dead end checker for maze traversal.
/// </summary>
/// <param name="addr">Address of the pointer that iterates over the matrix</param>
/// <param name="maze">Maze Matrix</param>
/// <param name="row">Row size</param>
/// <param name="col">Column size</param>
/// <returns></returns>
bool dead_end_status_traversal(mazeBlock* addr, vector<vector<mazeBlock>>& maze, int row, int col)
{
    linkedList<int> available_directions(3);

    // Left - 0
    if (addr->getCol() - 1 < 0)
    {
        available_directions.removeElement(0);
    }
    else if (maze[addr->getRow()][addr->getCol() - 1].getVisit())
    {
        available_directions.removeElement(0);
    }
    else if (addr->getWall()[0] == 1)
    {
        available_directions.removeElement(0);
    }

    // Right - 1
    if (addr->getCol() + 1 > col - 1)
    {
        available_directions.removeElement(1);
    }
    else if (maze[addr->getRow()][addr->getCol() + 1].getVisit())
    {
        available_directions.removeElement(1);
    }
    else if (addr->getWall()[1] == 1)
    {
        available_directions.removeElement(0);
    }

    // Up - 2
    if (addr->getRow() + 1 > row - 1)
    {
        available_directions.removeElement(2);
    }
    else if (maze[addr->getRow() + 1][addr->getCol()].getVisit())
    {
        available_directions.removeElement(2);
    }
    else if (addr->getWall()[2] == 1)
    {
        available_directions.removeElement(0);
    }

    // Down - 3
    if (addr->getRow() - 1 < 0)
    {
        available_directions.removeElement(3);
    }
    else if (maze[addr->getRow() - 1][addr->getCol()].getVisit())
    {
        available_directions.removeElement(3);
    }
    else if (addr->getWall()[3] == 1)
    {
        available_directions.removeElement(0);
    }

    if (available_directions.getSize() == 0)
    {
        return true;
    }

    else
    {
        return false;
    }
}

/// <summary>
/// Wallbreaker function for the maze generation algorithm.
/// </summary>
/// <param name="mazeStack">Stack that holds the maze blocks</param>
/// <param name="maze">Maze Matrix</param>
/// <param name="row">Row size of the matrix</param>
/// <param name="col">Column size of the matrix</param>
/// <param name="current">Address of the maze matrix iterator pointer</param>
void WallBreaker(mazeStack<mazeBlock>& mazeStack, vector<vector<mazeBlock>>& maze, int row, int col, mazeBlock* &current)
{
    linkedList<int> available_directions(3);
    mazeBlock top = mazeStack.removeTop();

    // Left - 0
    if (top.getCol() - 1 < 0)
    {
        available_directions.removeElement(0);
    }
    else if (maze[top.getRow()][top.getCol() - 1].getVisit())
    {
        available_directions.removeElement(0);
    }

    // Right - 1
    if (top.getCol() + 1 > col - 1)
    {
        available_directions.removeElement(1);
    }
    else if (maze[top.getRow()][top.getCol() + 1].getVisit())
    {
        available_directions.removeElement(1);
    }

    // Up - 2
    if (top.getRow() + 1 > row - 1)
    {
        available_directions.removeElement(2);
    }
    else if (maze[top.getRow() + 1][top.getCol()].getVisit())
    {
        available_directions.removeElement(2);
    }

    // Down - 3
    if (top.getRow() - 1 < 0)
    {
        available_directions.removeElement(3);
    }
    else if (maze[top.getRow() - 1][top.getCol()].getVisit())
    {
        available_directions.removeElement(3);
    }

    if (available_directions.getSize() != 0)
    {
        int random_direction = random_int_generator(available_directions.getSize() - 1);
        int dir = available_directions[random_direction];

        switch (dir)
        {
        case 0:
        {
            maze[top.getRow()][top.getCol() - 1].visitBlock();
            maze[top.getRow()][top.getCol()].breakWall(0);
            maze[top.getRow()][top.getCol() - 1].breakWall(1);
            top.breakWall(0);
            mazeStack.addTop(top);
            mazeStack.addTop(maze[top.getRow()][top.getCol() - 1]);
            current = &maze[top.getRow()][top.getCol() - 1];
            break;
        }
        case 1:
        {
            maze[top.getRow()][top.getCol() + 1].visitBlock();
            maze[top.getRow()][top.getCol()].breakWall(1);
            maze[top.getRow()][top.getCol() + 1].breakWall(0);
            top.breakWall(1);
            mazeStack.addTop(top);
            mazeStack.addTop(maze[top.getRow()][top.getCol() + 1]);
            current = &maze[top.getRow()][top.getCol() + 1];
            break;
        }
        case 2:
        {
            maze[top.getRow() + 1][top.getCol()].visitBlock();
            maze[top.getRow()][top.getCol()].breakWall(2);
            maze[top.getRow() + 1][top.getCol()].breakWall(3);
            top.breakWall(2);
            mazeStack.addTop(top);
            mazeStack.addTop(maze[top.getRow() + 1][top.getCol()]);
            current = &maze[top.getRow() + 1][top.getCol()];
            break;
        }
        case 3:
        {
            maze[top.getRow() - 1][top.getCol()].visitBlock();
            maze[top.getRow()][top.getCol()].breakWall(3);
            maze[top.getRow() - 1][top.getCol()].breakWall(2);
            top.breakWall(3);
            mazeStack.addTop(top);
            mazeStack.addTop(maze[top.getRow() - 1][top.getCol()]);
            current = &maze[top.getRow() - 1][top.getCol()];
            break;
        }
        }
    }

    else
    {
        mazeStack.addTop(top);
    }
}

/// <summary>
/// Traverser function for the generated matrix.
/// </summary>
/// <param name="mazeStack">Stack that holds the maze stack</param>
/// <param name="maze">Maze Matrix</param>
/// <param name="row">Row size of the maze matrix</param>
/// <param name="col">Column size of the maze matrix</param>
/// <param name="current">Address of the maze matrix iterator pointer</param>
void Traverser(mazeStack<mazeBlock>& mazeStack, vector<vector<mazeBlock>>& maze, int row, int col, mazeBlock* &current)
{
    linkedList<int> available_directions(3);
    mazeBlock top = mazeStack.removeTop();

    // Left - 0
    if (top.getCol() - 1 < 0)
    {
        available_directions.removeElement(0);
    }
    else if (maze[top.getRow()][top.getCol() - 1].getVisit())
    {
        available_directions.removeElement(0);
    }
    else if (top.getWall()[0] == 1)
    {
        available_directions.removeElement(0);
    }

    // Right - 1
    if (top.getCol() + 1 > col - 1)
    {
        available_directions.removeElement(1);
    }
    else if (maze[top.getRow()][top.getCol() + 1].getVisit())
    {
        available_directions.removeElement(1);
    }
    else if (top.getWall()[1] == 1)
    {
        available_directions.removeElement(1);
    }

    // Up - 2
    if (top.getRow() + 1 > row - 1)
    {
        available_directions.removeElement(2);
    }
    else if (maze[top.getRow() + 1][top.getCol()].getVisit())
    {
        available_directions.removeElement(2);
    }
    else if (top.getWall()[2] == 1)
    {
        available_directions.removeElement(2);
    }

    // Down - 3
    if (top.getRow() - 1 < 0)
    {
        available_directions.removeElement(3);
    }
    else if (maze[top.getRow() - 1][top.getCol()].getVisit())
    {
        available_directions.removeElement(3);
    }
    else if (top.getWall()[3] == 1)
    {
        available_directions.removeElement(3);
    }

    if (available_directions.getSize() != 0)
    {
        int random_direction = random_int_generator(available_directions.getSize() - 1);
        int dir = available_directions[random_direction];

        switch (dir)
        {
        case 0:
        {
            maze[top.getRow()][top.getCol() - 1].visitBlock();
            mazeStack.addTop(top);
            mazeStack.addTop(maze[top.getRow()][top.getCol() - 1]);
            current = &maze[top.getRow()][top.getCol() - 1];
            break;
        }
        case 1:
        {
            maze[top.getRow()][top.getCol() + 1].visitBlock();
            mazeStack.addTop(top);
            mazeStack.addTop(maze[top.getRow()][top.getCol() + 1]);
            current = &maze[top.getRow()][top.getCol() + 1];
            break;
        }
        case 2:
        {
            maze[top.getRow() + 1][top.getCol()].visitBlock();
            mazeStack.addTop(top);
            mazeStack.addTop(maze[top.getRow() + 1][top.getCol()]);
            current = &maze[top.getRow() + 1][top.getCol()];
            break;
        }
        case 3:
        {
            maze[top.getRow() - 1][top.getCol()].visitBlock();
            mazeStack.addTop(top);
            mazeStack.addTop(maze[top.getRow() - 1][top.getCol()]);
            current = &maze[top.getRow() - 1][top.getCol()];
            break;
        }
        }
    }

    else
    {
        mazeStack.addTop(top);
    }
}

/// <summary>
/// Maze generator engine
/// </summary>
/// <param name="numMaze">Number of the maze matrix</param>
/// <param name="row">Row size of the desired matrix</param>
/// <param name="col">Column size of the desired matrix</param>
void generateMaze(int numMaze, int row, int col)
{
    mazeBlock block;
    vector<mazeBlock> vec(col, block);
    vector<vector<mazeBlock>> maze(row, vec);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            mazeBlock m(i, j);
            maze[i][j] = m;
        }
    }

    mazeStack<mazeBlock> mazeStackMain, mazeBacktrack;
    mazeBlock* current = NULL;
    int broken_walls = 0;

    maze[0][0].visitBlock();
    mazeStackMain.addTop(maze[0][0]);
    current = &maze[0][0];

    //////////////////////////////////////////////////
    /// Brief Explanation of the algorithm
    /// 1. Add the initial block to the stack
    /// 2. Check for exit condition at the loop
    /// 3. Always check whether the main stack is empty or not
    /// 4. My current is the top of the backtract stack in case of backtrack
    /// 5. I hold the information of the stack that is on top of the backtrack stack.
    /// 6. In case that it is not dead end, I immediately add it to the top of the main stack
    /// 7. The ones that are left in the backtrack stack are dead ends anyway. 
    /// 8. I add them to the main stack afterwards. 
    //////////////////////////////////////////////////

    while (broken_walls < row * col - 1)
    {
        if (dead_end_status(current, maze, row, col))
        {
            if (!mazeStackMain.isEmpty())
            {
                while (!mazeStackMain.isEmpty() && dead_end_status(current, maze, row, col))
                {
                    mazeBlock top = mazeStackMain.removeTop();
                    mazeBacktrack.addTop(top);
                    top = mazeBacktrack.removeTop();
                    current = &maze[top.getRow()][top.getCol()];
                    mazeBacktrack.addTop(top);
                }

                mazeStackMain.addTop(mazeBacktrack.removeTop());
            }

            if (mazeStackMain.isEmpty())
            {
                break;
            }
        }

        else
        {
            WallBreaker(mazeStackMain, maze, row, col, current);
            broken_walls++;
        }
    }

    while (!mazeBacktrack.isEmpty())
    {
        mazeStackMain.addTop(mazeBacktrack.removeTop());
    }

    // Now we have the maze at hand.
    ofstream outputFile("maze_" + to_string(numMaze) + ".txt");
    outputFile << row << " " << col << endl;

    mazeStack<mazeBlock> printStack;

    while (!mazeStackMain.isEmpty())
    {
        mazeBlock temp = mazeStackMain.removeTop();
        printStack.addTop(temp);
    }

    while (!printStack.isEmpty())
    {
        mazeBlock temp = printStack.removeTop();
        outputFile << temp;
    }
}

/// <summary>
/// Line parser
/// </summary>
/// <param name="line">Line to be parsed</param>
/// <returns>Maze Block</returns>
mazeBlock parseLine(string line)
{
    int pos;

    pos = line.find("x=") + 2;
    int col = stoi(line.substr(pos, line.find(' ', pos) - pos));

    pos = line.find("y=") + 2;
    int row = stoi(line.substr(pos, line.find(' ', pos) - pos));

    int l = int(char(line[line.find("l=") + 2]) - '0');
    int r = int(char(line[line.find("r=") + 2]) - '0');
    int u = int(char(line[line.find("u=") + 2]) - '0');
    int d = int(char(line[line.find("d=") + 2]) - '0');

    mazeBlock block(row, col, l, r, u, d);
    return block;
}

/// <summary>
/// File to maze matrix function.
/// </summary>
/// <param name="file_name">File Name as string</param>
/// <returns>Maze Matrix</returns>
vector<vector<mazeBlock>> readFile(string file_name)
{
    ifstream file;
    file.open(file_name);
    string StackLine;

    mazeStack<mazeBlock> getSize;
    mazeStack<mazeBlock> getSizeBuf;

    int row = 0;
    int col = 0;

    // Discard the first line;
    getline(file, StackLine);

    // Parse the file to a stack.
    while (getline(file, StackLine))
    {
        mazeBlock block = parseLine(StackLine);
        getSize.addTop(block);
    }

    file.close();

    while (!getSize.isEmpty())
    {
        mazeBlock top = getSize.removeTop();

        if (top.getRow() > row)
        {
            row = top.getRow();
        }

        if (top.getCol() > col)
        {
            col = top.getCol();
        }

        getSizeBuf.addTop(top);
    }

    row++;
    col++;

    mazeBlock block;
    vector<mazeBlock> vec(col, block);
    vector<vector<mazeBlock>> maze(row, vec);

    while (!getSizeBuf.isEmpty())
    {
        mazeBlock top = getSizeBuf.removeTop();
        maze[top.getRow()][top.getCol()] = top;
    }

    return maze;
}

/// <summary>
/// Pathfinder engine
/// </summary>
/// <param name="mazeNum">Maze Number</param>
/// <param name="x_in"></param>
/// <param name="y_in"></param>
/// <param name="x_out"></param>
/// <param name="y_out"></param>
void pathFinder(int mazeNum, int mazeid, int x_in, int y_in, int x_out, int y_out)
{
    // Read the file into a matrix.
    vector<vector<mazeBlock>> path_maze = readFile("maze_" + to_string(mazeid) + ".txt");
    mazeStack<mazeBlock> mazeStackMain, mazeBacktrack;
    mazeBlock* current = NULL;
    bool dead_end = false;

    // I need to know the row and col counts of the maze.
    int rowSize = path_maze.size();
    int colSize = path_maze[0].size();

    // Pathfinding algo is not very different from the general maze generation algo.
    // Set the current pointer to the beginning of the maze.
    current = &path_maze[x_in][y_in];
    current->visitBlock();
    mazeStackMain.addTop(*current);

    // This is the exit condition. However, this will be checked for every single stack lift.
    // Because we don't want to miss out on the actual target coords getting hit.
    while ((current->getCol() != x_out) || (current->getRow() != y_out))
    {
        if (dead_end_status_traversal(current, path_maze, rowSize, colSize))
        {
            if (!mazeStackMain.isEmpty())
            {
                while (!mazeStackMain.isEmpty() && dead_end_status_traversal(current, path_maze, rowSize, colSize))
                {
                    mazeBlock top = mazeStackMain.removeTop();
                    mazeBacktrack.addTop(top);
                    top = mazeBacktrack.removeTop();
                    current = &path_maze[top.getRow()][top.getCol()];
                    mazeBacktrack.addTop(top);
                }

                mazeStackMain.addTop(mazeBacktrack.removeTop());
            }

            if (mazeStackMain.isEmpty())
            {
                break;
            }
        }

        else
        {
            Traverser(mazeStackMain, path_maze, rowSize, colSize, current);
        }
    }

    // Now we are printing the found path.
    ofstream outputFile("maze_" + to_string(mazeid) + "_" + to_string(x_in) + "_" + to_string(y_in) + "_" + to_string(x_out) + "_" + to_string(y_out) + ".txt");
    mazeStack<mazeBlock> printStack;

    // This is the print operation.
    while (!mazeStackMain.isEmpty())
    {
        mazeBlock temp = mazeStackMain.removeTop();
        printStack.addTop(temp);
    }

    while (!printStack.isEmpty())
    {
        mazeBlock temp = printStack.removeTop();
        outputFile << temp.getCol() << " " << temp.getRow() << endl;
    }
}

/// <summary>
/// Main function of the program. Everything happens here.
/// </summary>
/// <returns></returns>
int main()
{
    int mazeNum;
    int row_cnt;
    int col_cnt;

    cout << "Enter the number of mazes" << endl;
    cin >> mazeNum;
    cout << "Enter the number of rows and columns (M and N): " << endl;
    cin >> row_cnt >> col_cnt;

    for (int i = 1; i <= mazeNum; i++)
    {
        generateMaze(i, row_cnt, col_cnt);
    }

    cout << "All mazes are generated." << endl;

    int maze_ID;
    cout << "Enter a maze ID between 1 to " << mazeNum << " inclusive to find a path : " << endl;
    cin >> maze_ID;

    int x_entry;
    int y_entry;
    int x_exit;
    int y_exit;
    cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): " << endl;
    cin >> x_entry >> y_entry;
    cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): " << endl;
    cin >> x_exit >> y_exit;

    // Pathfinder function
    pathFinder(mazeNum, maze_ID, x_entry, y_entry, x_exit, y_exit);
    // Pathfinder function

    return 0;
}