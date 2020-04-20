#include <image.h>

#ifndef SINK_H
#define SINK_H

class Sink
{
     protected:
     Image* input;
     Image* input2;

     public:
     Sink(void);
     void SetInput(Image* inputImage){this->input = inputImage;};
     void SetInput2(Image* input2Image){this->input2 = input2Image;};
};

#endif
