#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <math.h>

/*Image::Image()
{
  width_ = 0;
  height_ = 0;
}*/

  /*Image::Image(unsigned w, unsigned h)
  {
    width_ = w;
    height_ = h;
  }*/

  //lighten an Image by increasing the luminance of every pixel by 0.1
  void Image::lighten()
  {
    for(unsigned x = 0; x < this->width(); x++)
    {
      for(unsigned y = 0; y < this->height(); y++)
      {
        double amount = 0.1;
        cs225::HSLAPixel & pixel = this->getPixel(x, y);

        if(pixel.l + amount <= 1.0 && pixel.l + amount >= 0.0)
          pixel.l += amount;
        else if(pixel.l + amount > 1.0)
          pixel.l = 1.0;
        else
          pixel.l = 0.0;
      }
    }
  }

  // Lighten an Image by increasing the lumincance of every pixel by amount
  void Image::lighten(double amount)
  {
    for(unsigned x = 0; x < this->width(); x++)
    {
      for(unsigned y = 0; y < this->height(); y++)
      {
        cs225::HSLAPixel & pixel = this->getPixel(x, y);

        if(pixel.l + amount <= 1.0 && pixel.l + amount >= 0.0)
          pixel.l += amount;
        else if(pixel.l + amount > 1.0)
          pixel.l = 1.0;
        else
          pixel.l = 0.0;
      }
    }
  }

  // Darken an Image by decreasing the luminance of every pixel by 0.1
  void Image::darken()
  {
    for(unsigned x = 0; x < this->width(); x++)
    {
      for(unsigned y = 0; y < this->height(); y++)
      {
        double amount = 0.1;
        cs225::HSLAPixel & pixel = this->getPixel(x, y);

        if(pixel.l - amount <= 1.0 && pixel.l - amount >= 0.0)
          pixel.l += amount;
        else if(pixel.l - amount > 1.0)
          pixel.l = 1.0;
        else
          pixel.l = 0.0;
      }
    }
  }

  // Darken an Image by decreasing the luminance of every pixel by amount
  void Image::darken (double amount)
  {
    for(unsigned x = 0; x < this->width(); x++)
    {
      for(unsigned y = 0; y < this->height();y++)
      {
        cs225::HSLAPixel & pixel = this->getPixel(x, y);

        if(pixel.l - amount <= 1.0 && pixel.l - amount >= 0.0)
          pixel.l -= amount;
        else if(pixel.l - amount > 1.0)
          pixel.l = 1.0;
        else
          pixel.l = 0.0;
      }
    }
  }

  //Saturates an Image by increasing the saturation of every pixel by 0.1
  void Image::saturate()
  {
    for(unsigned x = 0; x < this->width(); x++)
    {
      for(unsigned y = 0; y < this->height();y++)
      {
        double amount = 0.1;
        cs225::HSLAPixel & pixel = this->getPixel(x, y);

        if(pixel.s + amount <= 1.0 && pixel.s + amount >= 0.0)
          pixel.s += amount;
        else if(pixel.s + amount > 1.0)
          pixel.s = 1.0;
        else
          pixel.s = 0.0;
      }
    }
  }

  //Saturates an Image by increasing the saturation of every pixel by amount
  void Image::saturate(double amount)
  {
    for(unsigned x = 0; x < this->width(); x++)
    {
      for(unsigned y = 0; y < this->height();y++)
      {
        cs225::HSLAPixel & pixel = this->getPixel(x, y);

        if(pixel.s + amount <= 1.0 && pixel.s + amount >= 0.0)
          pixel.s += amount;
        else if(pixel.s + amount > 1.0)
          pixel.s = 1.0;
        else
          pixel.s = 0.0;
      }
    }
  }

  //Desaturates an Image by decreasing the saturation of every pixel by 0.1
  void Image::desaturate()
  {
    for(unsigned x = 0; x < this->width(); x++)
    {
      for(unsigned y = 0; y < this->height();y++)
      {
        double amount = 0.1;
        cs225::HSLAPixel & pixel = this->getPixel(x, y);

        if(pixel.s - amount <= 1.0 && pixel.s - amount >= 0.0)
          pixel.s -= amount;
        else if(pixel.s - amount > 1.0)
          pixel.s = 1.0;
        else
          pixel.s = 0.0;
      }
    }
  }

  //Desaturates an Image by decreasing the saturation of every pixel by amount
  void Image::desaturate(double amount)
  {
    for(unsigned x = 0; x < this->width(); x++)
    {
      for(unsigned y = 0; y < this->height();y++)
      {
        cs225::HSLAPixel & pixel = this->getPixel(x, y);

        if(pixel.s - amount <= 1.0 && pixel.s - amount >= 0.0)
          pixel.s -= amount;
        else if(pixel.s - amount > 1.0)
          pixel.s = 1.0;
        else
          pixel.s = 0.0;
      }
    }
  }

  //Turns the image grayscale (saturation = 0)
  void Image::grayscale()
  {
    for(unsigned x = 0; x < this->width(); x++)
    {
      for(unsigned y = 0; y < this->height();y++)
      {
        cs225::HSLAPixel & pixel = this->getPixel(x, y);
        pixel.s = 0.0;
      }
    }
  }

  //Rotates the color wheel by degrees
  void Image::rotateColor(double degrees)
  {
    for(unsigned x = 0; x < this->width(); x++)
    {
      for(unsigned y = 0; y < this->height();y++)
      {
        cs225::HSLAPixel & pixel = this->getPixel(x, y);

        if(pixel.h + degrees >= 0.0 && pixel.h + degrees <= 360.0)
          pixel.h += degrees;
        else if(pixel.h + degrees > 360.0){
          pixel.h = pixel.h + degrees - 360.0;
      } else{
        pixel.h = pixel.h + degrees + 360.0;
      }
    }
  }
}

  //Illinify the image
  void Image::illinify()
  {
    for(unsigned x = 0; x < this->width(); x++)
    {
      for(unsigned y = 0; y < this->height();y++)
      {
        cs225::HSLAPixel & pixel = this->getPixel(x, y);

        if ((pixel.h >= 0 && pixel.h <= 102.5) || (pixel.h > 282.5 && pixel.h < 360))
          pixel.h = 11;
        else
          pixel.h = 216;
      }
    }
  }

  //Scale the Image by a given factor
  //Need to take care of the situation when the new pic is smaller than the old pic
  void Image::scale(double factor)
  {
  //  std::cout << "factor: " << factor << std::endl;

      unsigned int new_width = factor * this->width();
      unsigned int new_height = factor * this->height();

    //  std::cout << "new width: " << new_width << std::endl;

      //Create a new PNG image with scaled width and height
      Image newImage;

      newImage.resize(new_width, new_height);

      //Map the pixels from the original image onto the new image
      for(unsigned x = 0; x < new_width; x++)
      {
        for(unsigned y = 0; y < new_height; y++)
        {
           if(factor >= 1.0){
             cs225::HSLAPixel & old_pixel = this->getPixel((int)(x / factor), (int)y / factor);
             cs225::HSLAPixel & new_pixel = newImage.getPixel(x, y);
             new_pixel = old_pixel;
           }else
           {
             cs225::HSLAPixel & old_pixel1 = this->getPixel(floor(x / factor), floor(y / factor));
             cs225::HSLAPixel & old_pixel2 = this->getPixel(ceil(x / factor), ceil(y / factor));
             cs225::HSLAPixel & new_pixel = newImage.getPixel(x, y);
             new_pixel.h = (old_pixel1.h + old_pixel2.h) / 2;
             new_pixel.l = (old_pixel1.l + old_pixel2.l) / 2;
             new_pixel.s = (old_pixel1.s + old_pixel2.s) / 2;
             new_pixel.a = (old_pixel1.a + old_pixel2.a) / 2;
           }

        }
      }
      *this = newImage;
    }


  //Scales the image to fit within the size (w x h)
  void Image::scale(unsigned w, unsigned h)
  {
    double width_ratio = w / this->width();
    double height_ratio = h / this->height();
  //  double factor;

    //std::cout << "double w: " << (double)w << std::endl;
  //  std::cout << "double h: " << (double)h << std::endl;

    if(width_ratio >= height_ratio)
    {
    //  std::cout << "double width_ratio: " << width_ratio << std::endl;
        scale(width_ratio);
        //factor = width_ratio;
    }else
    {
      //std::cout << "double height_ratio: " << height_ratio << std::endl;
        scale(height_ratio);
      //  factor = height_ratio;
    }


//    std::cout << "factor: " << factor << std::endl;

  //  scale(factor);
}
