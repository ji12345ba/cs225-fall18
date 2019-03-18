#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */


 ImageTraversal::ImageTraversal(PNG png, Point start, double tolerance)
 {
   image = png;
   start_point = start;
   tol = tolerance;
 }

double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal = NULL;
  end_switch = false;
  /*visited = new bool[traversal->image.width() * traversal->image.height()];

  //mark all Points as unvisited
  for(unsigned i = 0; i < traversal->image.width() * traversal->image.height(); i++)
  {
    visited[i] = false;
  }*/
}

/*ImageTraversal::Iterator::~Iterator()
{
  if(visited != NULL)
    delete[] visited;
}*/

ImageTraversal::Iterator::Iterator(ImageTraversal & traversal, Point start_point)
{
  /** @todo [Part 1] */
  this->traversal = &traversal;
  curr = traversal.peek();
  visited = new bool[traversal.image.width() * traversal.image.height()];

  //mark all Points as unvisited
  for(unsigned i = 0; i < traversal.image.width() * traversal.image.height(); i++)
  {
    visited[i] = false;
  }

  end_switch = false;

}

ImageTraversal::Iterator::Iterator(bool end)
{
  traversal = NULL;
  end_switch = end;
}


const HSLAPixel ImageTraversal::Iterator::pointToPixel(const Point & point) const
{
  const HSLAPixel & pixel = traversal->image.getPixel(point.x, point.y);
  return pixel;
}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if(!traversal->empty())
  {
    //visit current node
    curr = traversal->pop();
    visited[curr.y * traversal->image.width() + curr.x] = true;

    const HSLAPixel start_pixel = pointToPixel(traversal->start_point);

    //neighbors are born
    Point right(curr.x + 1, curr.y);
    Point below(curr.x, curr.y + 1);
    Point left(curr.x - 1, curr.y);
    Point above(curr.x, curr.y - 1);

    //check and add only valid points (within bounds, delta, unvisited)
    //check and add right
    if((right.x <= traversal->image.width() - 1)
      && visited[right.y * traversal->image.width() + right.x] == false
      && (traversal->calculateDelta(pointToPixel(right), start_pixel) < traversal->tol))
    {
      traversal->add(right);
    }

    //check and add below
    if((below.y <= traversal->image.height() - 1)
        && visited[below.y * traversal->image.width() + below.x] == false
          && (traversal->calculateDelta(pointToPixel(below), start_pixel) < traversal->tol))
    {
      traversal->add(below);
    }

    //check and add left
    if((curr.x >= 1)
      && (visited[left.y * traversal->image.width() + left.x] == false)
        && (traversal->calculateDelta(pointToPixel(left), start_pixel) < traversal->tol))
        {
          {
            traversal->add(left);
          }
        }


    //check and add above
    if((curr.y >= 1)
      && visited[above.y * traversal->image.width() + above.x] == false
        && (traversal->calculateDelta(pointToPixel(above), start_pixel) < traversal->tol))
    {
      traversal->add(above);
    }

    //move curr to the next unvisited point on stack/queue
    if(!traversal->empty())
    {
      curr = traversal->peek();

      while(!traversal->empty() && visited[curr.y * traversal->image.width() + curr.x] == true)
      {
        traversal->pop();
        if(!traversal->empty())
        {
          curr = traversal->peek();
        }
        else
        {
          traversal = NULL;
          end_switch = true;
          if(visited != NULL)
            delete[] visited;
          return *this;
        }
      }

    }

  }else
  {
    traversal = NULL;
    end_switch = true;
    if(visited != NULL)
      delete[] visited;
  }



  return *this;

}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return (this->end_switch != true);
}
