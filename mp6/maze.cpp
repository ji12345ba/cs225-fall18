#include "maze.h"
#include <vector>

using namespace std;

/* Default ctor*/
SquareMaze::SquareMaze()
{

}

/* Makes a new SquareMaze of the given height and width */
void SquareMaze::makeMaze(int width, int height)
{
  this->width = width;
  this->height = height;

  //initialize all walls as exist
  for (int i = 0; i < width * height; i++)
  {
    downWalls.push_back(true);
    rightWalls.push_back(true);
  }

DisjointSets ds;
ds.addelements(height * width);

int bound = 0;

while(bound < width * height - 1)
{
  int x = rand() % width;
  int y = rand() % height;
  bool break_wall = rand() % 2;

  // break right wall
  if (break_wall)
  {
    if (x < width - 1 && rightWalls[x + y * width] &&
      ds.find(x + y * width) != ds.find(x + 1 + y * width))
    {
      rightWalls[x + y * width] = 0;
      ds.setunion(ds.find(x + y * width), ds.find(x + 1 + y * width));
      bound++;
      }
    }
    else
    { //break down wall
      if (y < height - 1 && downWalls[x + y * width] &&
        ds.find(x + y * width) != ds.find(x + (y + 1) * width)) {
       downWalls[x + y * width] = 0;
       ds.setunion(ds.find(x + y * width), ds.find(x + (1 + y) * width));
       bound++;
        }
      }
    }
}

/* This uses your representation of the maze
 * to determine whether it is possible to travel
 * in the given direction from the square at coordinates (x,y)
 * dir = 0 - rightward step (x + 1)
 * dir = 1 - downward step (y + 1)
 * dir = 2 - leftward step (x - 1)
 * dir = 3 - upward step (y - 1)
 * cannot step off the maze or through a wall
*/
bool SquareMaze::canTravel(int x, int y, int dir) const
{
  //go right
  if (dir == 0)
    //if there's a wall (value is true) we can't go through
    //true when no right wall exist
    return !(rightWalls[x + y * width]);

  //go down
  if (dir == 1)
    return !(downWalls[x + y * width]);

  //go left
  if (dir == 2)
  {
    if (x == 0) return false; //goes out of bound
    return !(rightWalls[(x - 1) + y * width]);
  }

  //go up
  if (dir == 3)
  {
    if (y == 0) return false; //goes out of bound
    return !(downWalls[x + (y - 1) * width]);
   }
    return false;
}

/* Sets whether or not the specified wall exists.
 * dir = 0 - set right wall
 * dir = 1 - set down wall
*/
void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
  if (dir == 0)
  {
    rightWalls[x + y * width] = exists;
  }
  else if (dir == 1)
  {
    downWalls[x + y * width] = exists;
  }
}

/* Solves this SquareMaze.*/
vector<int> SquareMaze::solveMaze()
{
   vector<int> bottom_row;
   map<int, int> steps;
   vector<bool> visited;

   for(int i = 0; i < width * height; i++)
      visited.push_back(false); //mark all squares as unvisited

    queue<int> q;
    q.push(0);
    visited[0] = true;

    while(!q.empty())
    {
      int v = q.front();
      q.pop();
      int x = v % width;
      int y = v / width;
      if (y == height - 1) {
        bottom_row.push_back(v);
     }

          if (canTravel(x, y, 0) && !visited[v + 1])
          {
            steps.insert(pair<int, int> (v + 1, v));
            visited[v + 1] = true;
            q.push(v + 1);
          }
          if (canTravel(x, y, 1) && !visited[v + width])
          {
            steps.insert(pair<int, int> (v + width, v));
            visited[v + width] = true;
            q.push(v + width);
          }
          if (canTravel(x, y, 2) && !visited[v - 1])
          {
            steps.insert(pair<int, int> (v - 1, v));
            visited[v - 1] = true;
            q.push(v - 1);
          }
          if (canTravel(x, y, 3) && !visited[v - width])
          {
            steps.insert(pair<int, int> (v - width, v));
            visited[v - width] = true;
            q.push(v - width);
          }
        }

        vector<int> solution;
        int last = width - 1;
        while(bottom_row[last] == bottom_row[last - 1]) last -= 1;
        int start = bottom_row[last];

        while (start != 0)
        {
          int former = steps[start];
          if (start == former + 1) solution.push_back(0);
          else if (start == former - 1) solution.push_back(2);
          else if (start == former + width) solution.push_back(1);
          else if (start == former - width) solution.push_back(3);
          start = former;
        }
        reverse(solution.begin(),solution.end());

        return solution;
}

PNG * SquareMaze::drawMaze() const
{
    int new_width = width * 10 + 1;
    int new_height = height * 10 + 1;

    PNG * outPNG = new PNG(new_width, new_height);

  	//Blacken the leftmost column of pixels
    //except the entrance (1,0) through (9,0)
  	for(int x = 10; x < new_width; x++)
    {
      HSLAPixel & pixel = outPNG->getPixel(x, 0);
      pixel.l = 0;
    }
    //Blacken the entire topmost row
    for(int y = 0; y < new_height; y++)
    {
      HSLAPixel & pixel = outPNG->getPixel(0, y);
      pixel.l = 0;
    }

    // loop through each square in the maze
    for(int x = 0; x < width; x++)
    {
      for(int y = 0; y < height; y++)
      {
        //if right wall exists, blacken pixels with the specified coordinates
        if(rightWalls[x + y * width])
        {
          for(int k = 0; k < 11; k++)
          {
              HSLAPixel & pixel = outPNG->getPixel((x + 1) * 10, y * 10 + k);
              pixel.l = 0;
          }
        }
        //if bottom wall exists, blacken corresponding pixels
        if(downWalls[x + y * width])
        {
          for(int k = 0; k < 11; k++)
          {
              HSLAPixel & pixel = outPNG->getPixel(x * 10 + k, (y + 1) * 10);
              pixel.l = 0;
          }
        }
      }
    }

  	return outPNG;

}

/* This function calls drawMaze, then solveMaze;
  it modifies the PNG from drawMaze to show the solution vector and the exit */
PNG * SquareMaze::drawMazeWithSolution()
{
  PNG * outPNG = drawMaze();
  vector<int> solution = solveMaze();

  //starting points
  int x = 5;
  int y = 5;

  for(size_t i = 0; i < solution.size(); i++)
  {
    //right
    if(solution[i] == 0)
    {
      for(int k = 0; k < 10; k++)
      {
        HSLAPixel & pixel = outPNG->getPixel(x, y);
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
        x += 1;
      }
    }
    else if(solution[i] == 1)//down
    {
      for(int k = 0; k < 10; k++)
      {
        HSLAPixel & pixel = outPNG->getPixel(x, y);
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
        y += 1;
      }
    }
    else if(solution[i] == 2) //left
    {
      for(int k = 0; k < 10; k++)
      {
        HSLAPixel & pixel = outPNG->getPixel(x, y);
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
        x -= 1;
      }
    }
    else if(solution[i] == 3) //up
    {
      for(int k = 0; k < 10; k++)
      {
        HSLAPixel & pixel = outPNG->getPixel(x, y);
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
        y -= 1;
      }
    }
  }

  HSLAPixel & pixel = outPNG->getPixel(x, y);
  pixel.h = 0;
  pixel.s = 1;
  pixel.l = 0.5;
  pixel.a = 1;
  x -= 4;
  y += 5;
  //make the exit
  for(int k = 0; k < 9; k++)
  {
    HSLAPixel & pixel = outPNG->getPixel(x, y);
    pixel.l = 1;
    x += 1;
  }

  /*while(!solution.empty())
  {
    //step downward
    if(solution.front() == 1)
    {
      //bool out_of_bound = false;
      int temp = 0;
      for(int j = y; j < y + 11; j++)
      {
        //test if out of bound
        if(j < (int)outPNG->width())
        {
          HSLAPixel & pixel = outPNG->getPixel(x, j);
          pixel.h = 0;
          pixel.s = 1;
          pixel.l = 0.5;
          pixel.a = 1;
        }else{
        //  out_of_bound = true;
          temp = j; //store first index to be out of bound
          break;
        }
        temp = j;
      }
      //update y
    //  if(out_of_bound)
    //    y = temp;
    //  else
        y = temp;
      solution.erase(solution.begin()); //remove first element
    }

    //step rightward
    else if(solution.front() == 0)
    {
      //bool out_of_bound = false;
      int temp = 0;
      for(int i = x; i < x + 11; i++)
      {
        if(i < (int)outPNG->height())
        {
          HSLAPixel & pixel = outPNG->getPixel(i, y);
          pixel.h = 0;
          pixel.s = 1;
          pixel.l = 0.5;
          pixel.a = 1;
        }else
        {
        //  out_of_bound = true;
          temp = i;
          break;
        }
        temp = i;
      }
  //    if(out_of_bound)
        x = temp;
    //  else
    //    x = x + 11;
      solution.erase(solution.begin());
    }

    //step upward
    else if(solution.front() == 3)
    {
      //bool out_of_bound = false;
      int temp = 0;
      for(int j = y; j < y - 11; j--)
      {
        if(j > 0)
        {
          HSLAPixel & pixel = outPNG->getPixel(x, j);
          pixel.h = 0;
          pixel.s = 1;
          pixel.l = 0.5;
          pixel.a = 1;
        }else
        {
          temp = j;
          break;
        }
        temp = j;
      }
      y = temp;
      solution.erase(solution.begin());
    }
    //step leftward
    else if(solution.front() == 2)
    {
  //    bool out_of_bound = false;
      int temp = 0;
      for(int i = x; i < x - 11; i--)
      {
        if(i > 0)
        {
          HSLAPixel & pixel = outPNG->getPixel(i, y);
          pixel.h = 0;
          pixel.s = 1;
          pixel.l = 0.5;
          pixel.a = 1;
        }else
        {
          temp = i;
          break;
        }
      }
      x = temp;
      solution.erase(solution.begin());
    }
  }

  //make exit
  for(int k = 1; k <= 9; k++)
  {
    HSLAPixel & pixel = outPNG->getPixel(x * 10 + k, (y + 1) * 10);
    pixel.l = 1;
  }*/
  return outPNG;
}

/* part3: draws maze in the shape of an I block */
PNG * SquareMaze::drawCreativeMaze()
{
  int new_width = width * 10 + 1;
  int new_height = height * 10 + 1;

  PNG * outPNG = new PNG(new_width, new_height);

  //Blacken the entire topmost row
  //except the entrance (1,0) through (9,0)
  for(int x = 10; x < new_width; x++)
  {
    HSLAPixel & pixel = outPNG->getPixel(x, 0);
    pixel.l = 0;
  }

  //Blacken the leftmost column of pixels
  for(int y = 0; y < new_height; y++)
  {
    HSLAPixel & pixel = outPNG->getPixel(0, y);
    pixel.l = 0;
  }

  //set walls on inner sides of the I block
  //horizontal upper
  for(int x = 0; x < width * 0.25; x++)
  {
    setWall(x, height * 0.25, 1, true);
  }

  for(int x = width * 0.75; x < width; x++)
  {
    setWall(x, height * 0.25, 1, true);
  }

  //horizontal lower
  for(int x = 0; x < width * 0.25; x++)
  {
    setWall(x, height * 0.75 - 1, 1, true);
  }

  for(int x = width * 0.75; x < width; x++)
  {
    setWall(x, height * 0.75 - 1, 1, true);
  }

  //vertical left
  for(int y = height * 0.25; y < height * 0.75; y++)
  {
    setWall(width * 0.25 - 1, y, 0, true);
  }

  //vertical right
  for(int y = height * 0.25; y < height * 0.75; y++)
  {
    setWall(width * 0.75, y, 0, true);
  }

  // loop through each square in the maze
  for(int x = 0; x < width; x++)
  {
    for(int y = 0; y < height; y++)
    {
      if(!((y > height * 0.25 && y < height * 0.75 && x < width * 0.25) ||
        (y > height * 0.25 && y < height * 0.75 && x > width * 0.75)))
        {
          //if right wall exists, blacken pixels with the specified coordinates
          if(rightWalls[x + y * width])

          {
            for(int k = 0; k < 11; k++)
            {
                HSLAPixel & pixel = outPNG->getPixel((x + 1) * 10, y * 10 + k);
                pixel.l = 0;
            }
          }
          //if bottom wall exists, blacken corresponding pixels
          if(downWalls[x + y * width])
          {
            for(int k = 0; k < 11; k++)
            {
                HSLAPixel & pixel = outPNG->getPixel(x * 10 + k, (y + 1) * 10);
                pixel.l = 0;
            }
          }
        }
    }
  }

  return outPNG;
}

/* part3: draws I block maze with solution */
PNG * SquareMaze::drawCreativeMazeWithSolution()
{
  PNG * outPNG = drawCreativeMaze();
  vector<int> solution = solveMaze();

  //starting points
  int x = 5;
  int y = 5;

  for(size_t i = 0; i < solution.size(); i++)
  {
    //right
    if(solution[i] == 0)
    {
      for(int k = 0; k < 10; k++)
      {
        HSLAPixel & pixel = outPNG->getPixel(x, y);
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
        x += 1;
      }
    }
    else if(solution[i] == 1)//down
    {
      for(int k = 0; k < 10; k++)
      {
        HSLAPixel & pixel = outPNG->getPixel(x, y);
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
        y += 1;
      }
    }
    else if(solution[i] == 2) //left
    {
      for(int k = 0; k < 10; k++)
      {
        HSLAPixel & pixel = outPNG->getPixel(x, y);
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
        x -= 1;
      }
    }
    else if(solution[i] == 3) //up
    {
      for(int k = 0; k < 10; k++)
      {
        HSLAPixel & pixel = outPNG->getPixel(x, y);
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
        y -= 1;
      }
    }
  }

  HSLAPixel & pixel = outPNG->getPixel(x, y);
  pixel.h = 0;
  pixel.s = 1;
  pixel.l = 0.5;
  pixel.a = 1;
  x -= 4;
  y += 5;
  //make the exit
  for(int k = 0; k < 9; k++)
  {
    HSLAPixel & pixel = outPNG->getPixel(x, y);
    pixel.l = 1;
    x += 1;
  }

  return outPNG;
}
