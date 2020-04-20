#ifndef SOURCE_H
#define SOURCE_H

#include <image.h>
#include <string>

class Image;

class Source
{
     protected:
     Image* image;
     virtual void Execute()=0;

     public:
     Source(void);
     Image* GetOutput();
     virtual void Update();
     virtual std::string SourceName()=0;
};

class ConstantColor : public Source {

     protected:
     virtual void Execute();
     unsigned char r;
     unsigned char g;
     unsigned char b;

     public:
     ConstantColor(int height, int width, unsigned char r, unsigned char g, unsigned char b);
};

#endif
