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
     void SetInput(Image* input) {this->input = input;};
     void SetInput2(Image* input2) {this->input2 = input2;};

};

#endif
