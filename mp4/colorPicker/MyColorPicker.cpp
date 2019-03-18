#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

MyColorPicker::MyColorPicker(double decrement)
  : hue(240) , decrement(decrement) { }

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pixel(hue, 1.0, 1.0);
  if(hue >= 200)
    hue -= decrement;
  else
    hue += 360;
  return pixel;
}
