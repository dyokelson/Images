#include <image.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

Image::Image(void)
{
     this->width = 0;
     this->height = 0;
     this->pixel = (Pixel*) malloc(sizeof(Pixel));
}

Image::Image(Pixel *pixel)
{
     this->pixel = pixel;
}

Image::Image(Pixel *pixel, int width, int height)
{
     this->pixel = pixel;
     this->width = width;
     this->height = height;
}

Image::Image(Image &img)
{
     this->height = img.height;
     this->width = img.width;
     this->pixel = (Pixel*) malloc(sizeof(Pixel));
     this->pixel = img.pixel;
}

void Image::ResetSize(int width, int height)
{
     this->width = width;
     this->height = height;
     this->pixel = (Pixel*) malloc(width*height*sizeof(Pixel));
}

void Image::Update() {
     // ask it's source to update
     this->source->Update();
}
