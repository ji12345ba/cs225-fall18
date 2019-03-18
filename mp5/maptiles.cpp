/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    int rows = theSource.getRows();
    int columns = theSource.getColumns();

    MosaicCanvas * mosaic = new MosaicCanvas(rows, columns);
    vector<Point<3>> avg_colors;
    //value give the index of the corresponding point
    map<Point<3>, int> tileMap;

    //store the points representing the average color of the tiles in a vector
    for(size_t i = 0; i < theTiles.size(); i++)
    {
      LUVAPixel avg_c = theTiles[i].getAverageColor();
      Point<3> c = convertToXYZ(avg_c);
      avg_colors.push_back(c);
      tileMap[c] = i; // map the Point to the index of the tile
    }

    //use the vector of average colors to generate a kdtree
    KDTree<3> avg_points(avg_colors);

    for(int r = 0; r < rows; r++)
    {
      for(int c = 0; c < columns; c++)
      {
        //the point corresponding to the color of the region to be matched with
        Point<3> query = convertToXYZ(theSource.getRegionColor(r, c));
        //return the point representing the closest color from the tiles to be picked from
        Point<3> result = avg_points.findNearestNeighbor(query);

      /*  TileImage match_tile;
        for(TileImage t : theTiles)
        {
          if(t.getAverageColor() == result)
            match_tile = t;
        }*/
        //map back from point to color to image??
        mosaic->setTile(r, c, &theTiles[tileMap[result]]);
      }

    }

    return mosaic;
}
