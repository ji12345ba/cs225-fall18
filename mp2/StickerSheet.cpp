#include "StickerSheet.h"
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace cs225;
/*Initializes this StickerSheet with a base picture
and the ability to hold a max number of stickers (Images) with indices 0 through max */
StickerSheet::StickerSheet(const Image & picture, unsigned max)
{
  count = 0; //no sticker in the sheet
  layer = -1; // layer goes up to 0 when a new sticker is created
  max_stickers = max;
  base = picture;
  stickers = new Image[max_stickers];
  sticker_x = new int[max_stickers];
  sticker_y = new int[max_stickers];
}

StickerSheet::~StickerSheet()
{
  if(stickers != NULL || sticker_x != NULL || sticker_y != NULL)
  {
    delete[] stickers;
    delete[] sticker_x;
    delete[] sticker_y;
  }
}

StickerSheet::StickerSheet(const StickerSheet & other)
{
  copy(other);
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other)
{
  if(this != &other)
  {
    delete[] stickers;
    delete[] sticker_x;
    delete[] sticker_y;
    copy(other);
  }
  return *this;
}

/*Modifies the maximum number of stickers that can be stored on this StickerSheet
without changing existing stickers' indices*/
void StickerSheet::changeMaxStickers(unsigned max)
{
  if((int)max < max_stickers)
  {
    Image * new_stickers = new Image[max];
    if (count > (int) max) {
      count = max;
      layer = count - 1;
    }
    for(int i = 0; i < (int)count; i++)
    {
      new_stickers[i] = stickers[i];
    }
    delete[] stickers;
    stickers = new_stickers;
  }else
  {
    Image * temp = new Image[max];
    for(int i = 0; i < (int) count; i++)
    {
      temp[i] = stickers[i];
    }
    delete[] stickers;
    stickers = temp;
  }
  max_stickers = max;
}

/*Adds a sticker to the StickerSheet,
so that the top-left of the sticker's Image is at (x, y) on the StickerSheet*/
int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y)
{
  if(count+1 <= max_stickers)
  {
    stickers[count] = sticker;

    sticker_x[count] = x;
    sticker_y[count++] = y; //increase num of stickers by one after a sticker is added

    layer++;

  /*  std::cout << "number of current stickers: " << count << std::endl;
    std::cout << "number of current layers: " << layer << std::endl;*/

    return layer; //Return the layer index
  }
  else{
    return -1;
  }

}

//Changes the x and y coordinates of the Image in the specified layer
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y)
{
  if ((int) index < count)
  {
    sticker_x[index] = x;
    sticker_y[index] = y;

  }else
  {
    return false;
  }
  return true;
}

//Removes the sticker at the given zero-based layer index
void StickerSheet::removeSticker(unsigned index)
{
  //Image * sticker = new Image(stickers[index]);
  assert(index < (unsigned) count);
  count--;
  layer--;
  for(int i = index; i < count; i++)
  {
    stickers[i] = stickers[i + 1];
    sticker_x[i] = sticker_x[i + 1];
    sticker_y[i] = sticker_y[i + 1];
  }
}

//Returns a pointer to the sticker at the specified index, not a copy of it
Image * StickerSheet::getSticker(unsigned index) const
{
  if (index >= (unsigned) count) return NULL;
  return &stickers[index];
}

//Renders the whole StickerSheet on one Image and returns that Image
//manipulates pxiels to modify the base picture
// need to scale the picture if stickers outside of the bounds
Image StickerSheet::render() const
{
  //makes a copy of the base picture
  Image image(base);

  unsigned int sticker_x_max = image.width();
  unsigned int sticker_y_max = image.height();

  // Get the boundaries of x and y of all stickers
  for(int i = 0; i < count; i++)
  {
    sticker_x_max = std::max(sticker_x_max, sticker_x[i] + stickers[i].width());
    sticker_y_max = std::max(sticker_y_max, sticker_y[i] + stickers[i].height());
  }

  //scale the picture first if stickers are out of bounds
  if(sticker_x_max > base.width() || sticker_y_max > base.height())
  {
    image.scale(sticker_x_max, sticker_y_max);
  }

  for(int s = 0; s < count; s++)
  {
  /*  if(sticker_x_max > base.width() || sticker_y_max > base.height())
    {
      image.scale(sticker_x_max, sticker_y_max);
    }*/

    for(unsigned x = 0; x < image.width(); x++)
    {

      for(unsigned y = 0; y < image.height(); y++)
      {
        if((int)x >= sticker_x[s] && x < sticker_x[s] + stickers[s].width())
        {
          //std::cout << "sticker_x[s] " << sticker_x[s] << std::endl;
          //std::cout << "stickers[s].width() " << stickers[s].width() << std::endl;

          if((int)y >= sticker_y[s] && y < sticker_y[s] + stickers[s].height())
          {
            HSLAPixel & image_pixel = image.getPixel(x,y);
            //std::cout << "modified image wdth: " << image.width() << std::endl;
            HSLAPixel & sticker_pixel = stickers[s].getPixel(
              (int)x - (int)sticker_x[s], (int)y - (int)sticker_y[s]);

            if(sticker_pixel.a != 0) {
              image_pixel = sticker_pixel;
            //  assert(sticker_pixel.a == 1);
            }

          }
        }
      /*  if((int)x >= sticker_x[s] && x <= sticker_x[s] + stickers[s].width()
          && (int)y >= sticker_y[s] && y <= sticker_y[s] + stickers[s].height())*/
      /*    {
            HSLAPixel & image_pixel = image.getPixel(x,y);
            std::cout << "modified image wdth: " << image.width() << std::endl;
            HSLAPixel & sticker_pixel = stickers[s].getPixel(x - sticker_x[s] - 1, y - sticker_y[s] - 1);

            if(sticker_pixel.a != 0)
            image_pixel = sticker_pixel;

          }*/
      }
    }
  }
   return image;
}

void StickerSheet::copy(const StickerSheet& other)
{
  max_stickers = other.max_stickers;
  count = other.count;
  layer = other.layer;
  base = other.base;

  stickers = new Image[max_stickers];
  sticker_x = new int[max_stickers];
  sticker_y = new int[max_stickers];

  for(int i = 0; i < max_stickers; i++)
  {
    stickers[i] = other.stickers[i];
    sticker_x[i] = other.sticker_x[i];
    sticker_y[i] = other.sticker_y[i];
  }


}
