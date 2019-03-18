#include "Image.h"
#include "StickerSheet.h"
#include <iostream>

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  //read from and write to file

  Image base, sticker_1, sticker_2, sticker_3, sticker_4,
     sticker_5,sticker_6, sticker_7, result;
  base.readFromFile("community.png");
  base.scale(2.0);
  sticker_1.readFromFile("wade.png");
  sticker_1.scale(0.8);
  sticker_2.readFromFile("me.png");
  sticker_2.scale(0.3);
  sticker_3.readFromFile("segfaults.png");
  sticker_4.readFromFile("memoryleak.png");
  sticker_5.readFromFile("cs225.png");
  sticker_5.scale(0.7);
  sticker_6.readFromFile("TA.png");
  sticker_6.scale(0.7);
  sticker_7.readFromFile("CA.png");
  sticker_7.scale(0.5);

  StickerSheet sticker_sheet(base,7);

  sticker_sheet.addSticker(sticker_1, 1120, 140);
  sticker_sheet.addSticker(sticker_2, 400, 155);
  sticker_sheet.addSticker(sticker_3, 800, 700);
  sticker_sheet.addSticker(sticker_4, 900, 900);
  sticker_sheet.addSticker(sticker_5, 1960, 855);
  sticker_sheet.addSticker(sticker_6, 1810, 560);
  sticker_sheet.addSticker(sticker_7, 1670, 700);

  result = sticker_sheet.render();

  std::cout << "Adding stickers..." << std::endl;
  result.writeToFile("myImage.png");

  return 0;
}
