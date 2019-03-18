#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    SquareMaze maze;
    PNG * output;
    maze.makeMaze(50, 50);
    //output = maze.drawCreativeMaze();
    output = maze.drawCreativeMazeWithSolution();
    output->writeToFile("creative.png");
    return 0;
}
