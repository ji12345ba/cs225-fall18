
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  PNG grey;
  grey.readFromFile("adventuretime.png");
  FloodFilledImage ffi1(grey);
  DFS j1(grey, Point(111,338), 0.19);//yellow
  DFS j2(grey, Point(215,487), 0.19);
  DFS j3(grey, Point(283,458), 0.05);//dark red
  DFS j4(grey, Point(257,465), 0.19);//light red
  DFS j5(grey, Point(275,432), 0.19);
  DFS j6(grey, Point(388,408), 0.19);
  DFS j7(grey, Point(787,322), 0.19);

  BFS f1(grey, Point(544,273), 0.19);//skin
  BFS f2(grey, Point(521,425), 0.19);//light blue
  BFS f3(grey, Point(553,499), 0.19);//light blue
  BFS f4(grey, Point(755,459), 0.19);//light blue
  BFS f5(grey, Point(472,487), 0.19);//skin
  BFS f6(grey, Point(484,561), 0.19);//skin
  BFS f7(grey, Point(454,591), 0.19);//skin
  BFS f8(grey, Point(749,478), 0.19);//skin
  BFS f9(grey, Point(683,586), 0.19);//skin
  BFS f10(grey, Point(562,609), 0.19);//dark blue
  BFS f11(grey, Point(699,644), 0.19);//dark blue
  BFS f12(grey, Point(769,363), 0.05); //light green
  BFS f17(grey, Point(740,434), 0.05); //dark green
  BFS f13(grey, Point(875,373), 0.19);//light green
  BFS f14(grey, Point(887,420), 0.19);//dark green
  BFS f15(grey, Point(779,483), 0.19); //light blue
  BFS f16(grey, Point(630,676), 0.19); //dark blue

  DFS w1(grey, Point(0, 0), 0.2);
  DFS w2(grey, Point(155, 346), 0.2);
  DFS w3(grey, Point(307, 318), 0.2);
  DFS w4(grey, Point(257, 442), 0.2);
  DFS w5(grey, Point(270, 443), 0.2);
  DFS w6(grey, Point(282, 442), 0.2);
  DFS w7(grey, Point(472, 230), 0.2);
  DFS w8(grey, Point(417, 713), 0.2);
  DFS w9(grey, Point(477, 538), 0.2);
  DFS w10(grey, Point(646, 733), 0.2);

  HSLAPixel yellow(41, 0.92, 0.56);
  HSLAPixel pink(358, 0.84, 0.71);
  HSLAPixel dark_red(13.5, 1.0, 0.27);
  HSLAPixel light_blue(199, 0.92, 0.42);
  HSLAPixel dark_blue(207, 0.84, 0.39);
  HSLAPixel light_green(103, 0.18, 0.65);
  HSLAPixel dark_green(96, 0.5, 0.47);
  HSLAPixel skin(18, 0.91, 0.91);
  HSLAPixel white(0, 0, 1.0);

  SolidColorPicker y(yellow);
  SolidColorPicker p(pink);
  SolidColorPicker dr(dark_red);
  SolidColorPicker lb(light_blue);
  SolidColorPicker db(dark_blue);
  SolidColorPicker lg(light_green);
  SolidColorPicker dg(dark_green);
  SolidColorPicker s(skin);
  SolidColorPicker w(white);

  ffi1.addFloodFill(j1,y);
  ffi1.addFloodFill(j2, y);
  ffi1.addFloodFill(j3, dr);
  ffi1.addFloodFill(j4, p);
  ffi1.addFloodFill(j5, y);
  ffi1.addFloodFill(j6, y);
  ffi1.addFloodFill(j7, y);

  ffi1.addFloodFill(f1, s);
  ffi1.addFloodFill(f2, lb);
  ffi1.addFloodFill(f3, lb);
  ffi1.addFloodFill(f4, lb);
  ffi1.addFloodFill(f5, s);
  ffi1.addFloodFill(f6, s);
  ffi1.addFloodFill(f7, s);
  ffi1.addFloodFill(f8, s);
  ffi1.addFloodFill(f9, s);
  ffi1.addFloodFill(f10, db);
  ffi1.addFloodFill(f11, db);
  ffi1.addFloodFill(f12, lg);
  ffi1.addFloodFill(f17, dg);
  ffi1.addFloodFill(f13, lg);
  ffi1.addFloodFill(f14, dg);
  ffi1.addFloodFill(f15, lb);
  ffi1.addFloodFill(f16, db);

  ffi1.addFloodFill(w2, w);
  ffi1.addFloodFill(w3, w);
  ffi1.addFloodFill(w4, w);
  ffi1.addFloodFill(w5, w);
  ffi1.addFloodFill(w6, w);
  ffi1.addFloodFill(w7, w);
  ffi1.addFloodFill(w8, w);
  ffi1.addFloodFill(w10, w);
  ffi1.addFloodFill(w1, w);
  ffi1.addFloodFill(w9, w);

  Animation decolor = ffi1.animate(12000);

  PNG lastFrame = decolor.getFrame( decolor.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  decolor.write("myFloodFill.gif");

  return 0;
}
