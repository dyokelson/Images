#ifndef IMAGE_H
#define IMAGE_H

#include <source.h>

class Source;

struct Pixel
{
     unsigned char r,g,b;
};

class Image
{
     Pixel *pixel;
     int width;
     int height;
     Source *source;

     public:
     Image(void);
     Image(Pixel *pixel);
     Image(Pixel *pixel, int width, int height);
     Image(Image &img);
     void ResetSize(int width, int height);
     int getWidth() { return width;};
     int getHeight(){ return height;};
     void setWidth(int width) { this->width = width;};
     void setHeight(int height){this->height = height;};
     Pixel* getPixel(){return pixel;};
     void setPixel(Pixel* pixel){ this->pixel = pixel;};
     void Update();
     void setSource(Source *source){ this->source = source;};
};

#endif
