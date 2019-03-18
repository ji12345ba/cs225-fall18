/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"

class StickerSheet{
public:
  /*Initializes this StickerSheet with a base picture
  and the ability to hold a max number of stickers (Images) with indices 0 through max */
  StickerSheet(const Image & picture, unsigned max);

  ~StickerSheet();
  StickerSheet(const StickerSheet & other); //copy ctor
  const StickerSheet & operator=(const StickerSheet & other);

  /*Modifies the maximum number of stickers that can be stored on this StickerSheet
  without changing existing stickers' indices*/
  void changeMaxStickers(unsigned max);

  /*Adds a sticker to the StickerSheet,
 so that the top-left of the sticker's Image is at (x, y) on the StickerSheet*/
  int addSticker(Image &sticker, unsigned x, unsigned y);

  //Changes the x and y coordinates of the Image in the specified layer
  bool translate(unsigned index, unsigned x, unsigned y);

  //Removes the sticker at the given zero-based layer index
  void removeSticker(unsigned index);

  //Returns a pointer to the sticker at the specified index, not a copy of it
  Image * getSticker(unsigned index) const;

  //Renders the whole StickerSheet on one Image and returns that Image
  Image render() const;

  void copy(const StickerSheet& other);

private:
  int max_stickers;
  //num of stickers in the StickerSheet (1 for one sticker)
  int count;
  //num of layers (0 for first sticker)
  int layer;
  Image base;
  Image * stickers;
  // array that stores the top left x coodinates of the stickers
  //index 0 is first sticker
  int * sticker_x;
  // array that stores the top lefy y coordinates of the stickers
  int * sticker_y;

};
