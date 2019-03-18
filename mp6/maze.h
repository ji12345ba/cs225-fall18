#pragma once
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

#include "cs225/PNG.h"
#include "dsets.h"

using namespace cs225;
using namespace std;

class SquareMaze
{
public:
  /* Default ctor*/
  SquareMaze();

  /* Makes a new SquareMaze of the given height and width */
  void makeMaze(int width, int height);

  /* This uses your representation of the maze
    to determine whether it is possible to travel
    in the given direction from the square at coordinates (x,y)
  */
  bool canTravel(int x, int y, int dir) const;

  /* Sets whether or not the specified wall exists.*/
  void setWall(int x, int y, int dir, bool exists);

  /* Solves this SquareMaze.*/
  vector<int> solveMaze();

  /* Draws the maze without the solution. */
  PNG * drawMaze() const;

  /* This function calls drawMaze, then solveMaze;
    it modifies the PNG from drawMaze to show the solution vector and the exit */
  PNG * drawMazeWithSolution();

  /* part3: draws maze in the shape of an I block */
  PNG * drawCreativeMaze();

  /* part3: draws I block maze with solution */
  PNG * drawCreativeMazeWithSolution();

private:
  //1-D vectors to store the status of the walls of all grids in the maze
  vector<bool> downWalls;
  vector<bool> rightWalls;

  int width;
  int height;
};
