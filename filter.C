#include <filter.h>
#include <stdlib.h>
#include <stdio.h>
#include <logging.h>
#include <string>

Filter::Filter(void)
{
}

void Filter::Update()
{
     char msg[1024];
     if (input == GetOutput() || input2 == GetOutput()) {
         char error[1024];
         sprintf(error, "%s: Input and Output should be different", SourceName().c_str());
         DataFlowException e(SourceName().c_str(), error);
         throw e;
     }
     if (input) {
         sprintf(msg, "%s: about to update input1", SourceName().c_str());
         Logger::LogEvent(msg);
         this->input->Update();
     }

     if (this->input2) {
         sprintf(msg, "%s: about to update input2", SourceName().c_str());
         Logger::LogEvent(msg);
         this->input2->Update();
     }
     sprintf(msg, "%s: about to execute", SourceName().c_str());
     Logger::LogEvent(msg);
     Execute();
     sprintf(msg, "%s: done executing", SourceName().c_str());
     Logger::LogEvent(msg);
}

Mirror::Mirror(void){}

std::string Mirror::SourceName() {
     return "Mirror";
}

void Mirror::Execute() {
    if (!input) {
         char error[1024];
         sprintf(error, "%s: no input 1!", SourceName().c_str());
         DataFlowException e(SourceName().c_str(), error);
         throw e;
    }
    int i;
    image->ResetSize(input->getWidth(),input->getHeight());
    Pixel* out_pix = image->getPixel();
    Pixel* in_pix = input->getPixel();
    for (int i=0; i<image->getWidth()*image->getHeight(); i++) {
         int row = i/image->getWidth();
         int out_col = i-(row*image->getWidth());
         int in_col = image->getWidth()-out_col-1;
         int in_index = in_col + (row*input->getWidth());
         out_pix[i].r = in_pix[in_index].r;
         out_pix[i].g = in_pix[in_index].g;
         out_pix[i].b = in_pix[in_index].b;
    }
}

Rotate::Rotate(void){}

std::string Rotate::SourceName() {
     return "Rotate";
}

void Rotate::Execute() {
    if (!input) {
         char error[1024];
         sprintf(error, "%s: no input 1!", SourceName().c_str());
         DataFlowException e(SourceName().c_str(), error);
         throw e;
    }
    int i;
    image->ResetSize(input->getHeight(),input->getWidth());//swap height/width
    Pixel* out_pix = image->getPixel();
    Pixel* in_pix = input->getPixel();
    for (int i=0; i<image->getWidth()*image->getHeight(); i++) {
         int out_row = i/image->getWidth();
         int out_col = i-(out_row*image->getWidth());
         int in_col = out_row;
         int in_row = image->getWidth() - out_col - 1;

         int l = in_col + (in_row*input->getWidth());
         out_pix[i].r = in_pix[l].r;
         out_pix[i].g = in_pix[l].g;
         out_pix[i].b = in_pix[l].b;
         }
}

Subtract::Subtract(void){}

std::string Subtract::SourceName() {
     return "Subtract";
}

unsigned char SubtractPixels(unsigned char p1, unsigned char p2) {
    if (p1 <= p2) {
        return 0;
    } else {
        return p1-p2;
    }

}

void Subtract::Execute() {
    if (!input) {
         char error[1024];
         sprintf(error, "%s: no input 1!", SourceName().c_str());
         DataFlowException e(SourceName().c_str(), error);
         throw e;

    }
    if (!input2) {
         char error[1024];
         sprintf(error, "%s: no input 2!", SourceName().c_str());
         DataFlowException e(SourceName().c_str(), error);
         throw e;

    }
    if ((input->getHeight() != input2->getHeight()) && (input->getWidth() != input2->getWidth())) {
            char error[1024];
            sprintf(error, "%s: dimensions must match: %d, %d", SourceName().c_str(), input->getHeight(), input2->getHeight());
            DataFlowException e(SourceName().c_str(), error);
            throw e;
    }
    int i;
    image->ResetSize(input->getWidth(), input->getHeight());
    Pixel* out_pix = image->getPixel();
    Pixel* in_pix1 = input->getPixel();
    Pixel* in_pix2 = input2->getPixel();
    for (i=0; i < image->getHeight()*image->getWidth(); i++) {
        out_pix[i].r = SubtractPixels(in_pix1[i].r, in_pix2[i].r);
        out_pix[i].g = SubtractPixels(in_pix1[i].g, in_pix2[i].g);
        out_pix[i].b = SubtractPixels(in_pix1[i].b, in_pix2[i].b);
    }
}

Grayscale::Grayscale(void){}

std::string Grayscale::SourceName() {
     return "Grayscale";
}

void Grayscale::Execute() {
    if (!input) {
         char error[1024];
         sprintf(error, "%s: no input 1!", SourceName().c_str());
         DataFlowException e(SourceName().c_str(), error);
         throw e;
    }
    int i;
    image->ResetSize(input->getWidth(), input->getHeight());
    Pixel* out_pix = image->getPixel();
    Pixel* in_pix = input->getPixel();
    for (i=0; i < image->getHeight()*image->getWidth(); i++) {
         out_pix[i].r = in_pix[i].r/5+in_pix[i].g/2+in_pix[i].b/4;
         out_pix[i].g = in_pix[i].r/5+in_pix[i].g/2+in_pix[i].b/4;
         out_pix[i].b = in_pix[i].r/5+in_pix[i].g/2+in_pix[i].b/4;
    }
}

Blur::Blur(void){}

std::string Blur::SourceName() {
     return "Blur";
}

void Blur::Execute() {
    if (!input) {
         char error[1024];
         sprintf(error, "%s: no input 1!", SourceName().c_str());
         DataFlowException e(SourceName().c_str(), error);
         throw e;
    }
    int i;
    image->ResetSize(input->getWidth(), input->getHeight());
    Pixel* out_pix = image->getPixel();
    Pixel* in_pix1 = input->getPixel();

    for (int i=0; i<image->getWidth()*image->getHeight(); i++) {
         int row = i/image->getWidth();
         int col = i-(row*image->getWidth());
         if ((row == 0) || (row == image->getHeight()-1) || (col == 0) || (col == image->getWidth()-1)) {
             out_pix[i].r = in_pix1[i].r;
             out_pix[i].g = in_pix1[i].g;
             out_pix[i].b = in_pix1[i].b;
         } else {
             int l = col + (row*input->getWidth());
             int topleft = (col-1) + ((row-1)*input->getWidth());
             int top = (col) + ((row-1)*input->getWidth());
             int topright = (col+1) + ((row-1)*input->getWidth());
             int left = (col-1) + ((row)*input->getWidth());
             int right = (col+1) + ((row)*input->getWidth());
             int botleft = (col-1) + ((row+1)*input->getWidth());
             int bottom = (col) + ((row+1)*input->getWidth());
             int botright = (col+1) + ((row+1)*input->getWidth());
             out_pix[i].r = in_pix1[topleft].r/8+in_pix1[top].r/8+
                in_pix1[topright].r/8+in_pix1[left].r/8+in_pix1[right].r/8+
                in_pix1[botleft].r/8+in_pix1[bottom].r/8+in_pix1[botright].r/8;
             out_pix[i].g = in_pix1[topleft].g/8+in_pix1[top].g/8+
                in_pix1[topright].g/8+in_pix1[left].g/8+in_pix1[right].g/8+
                in_pix1[botleft].g/8+in_pix1[bottom].g/8+in_pix1[botright].g/8;
             out_pix[i].b = in_pix1[topleft].b/8+in_pix1[top].b/8+
                in_pix1[topright].b/8+in_pix1[left].b/8+in_pix1[right].b/8+
                in_pix1[botleft].b/8+in_pix1[bottom].b/8+in_pix1[botright].b/8;
         }
    }
}

Shrinker::Shrinker(void){}

std::string Shrinker::SourceName() {
     return "Shrinker";
}

void Shrinker::Execute()
{    if (!input) {
         char error[1024];
         sprintf(error, "%s: no input 1!", SourceName().c_str());
         DataFlowException e(SourceName().c_str(), error);
         throw e;
     }
     image->ResetSize(input->getWidth()/2, input->getHeight()/2);
     Pixel* out_pix = image->getPixel();
     Pixel* in_pix = input->getPixel();

     for (int i=0; i<(image->getWidth()*image->getHeight()); i++)
     {
          int row = i/image->getWidth();
          int col = i- (row*image->getWidth());
          int in_row = 2*row;
          int in_col = 2*col;
          int j = in_col+(in_row*input->getWidth());

          out_pix[i].r = in_pix[j].r;
          out_pix[i].g = in_pix[j].g;
          out_pix[i].b = in_pix[j].b;
      }
}

LRCombine::LRCombine(void)
{
}

std::string LRCombine::SourceName() {
     return "LRCombine";
}

void LRCombine::Execute()
{
      if (!input) {
           char error[1024];
           sprintf(error, "%s: no input 1!", SourceName().c_str());
           DataFlowException e(SourceName().c_str(), error);
           throw e;

      }
      if (!input2) {
           char error[1024];
           sprintf(error, "%s: no input 2!", SourceName().c_str());
           DataFlowException e(SourceName().c_str(), error);
           throw e;

      }
      if (input->getHeight() != input2->getHeight()) {
              char error[1024];
              sprintf(error, "%s: heights must match: %d, %d", SourceName().c_str(), input->getHeight(), input2->getHeight());
              DataFlowException e(SourceName().c_str(), error);
              throw e;
     }
     int new_width = input->getWidth() + input2->getWidth();
     image->ResetSize(new_width, input->getHeight());
     Pixel* out_pix = image->getPixel();
     Pixel* in_pix1 = input->getPixel();
     Pixel* in_pix2 = input2->getPixel();

     for (int i=0; i<image->getWidth()*image->getHeight(); i++)
     {
          int row = i/image->getWidth();
          int col = i - (row*image->getWidth());
          if (col < input->getWidth())
          {
                int l = col + (row*input->getWidth());
                out_pix[i].r = in_pix1[l].r;
                out_pix[i].g = in_pix1[l].g;
                out_pix[i].b = in_pix1[l].b;
           } else {
                int r = ((col-input->getWidth()) + (row*input2->getWidth()));
                out_pix[i].r = in_pix2[r].r;
                out_pix[i].g = in_pix2[r].g;
                out_pix[i].b = in_pix2[r].b;
           }
      }
}

TBCombine::TBCombine(void)
{
}

std::string TBCombine::SourceName() {
     return "TBCombine";
}

void TBCombine::Execute()
{    if (!input) {
         char error[1024];
         sprintf(error, "%s: no input 1!", SourceName().c_str());
         DataFlowException e(SourceName().c_str(), error);
         throw e;
    }
    if (!input2) {
         char error[1024];
         sprintf(error, "%s: no input 2!", SourceName().c_str());
         DataFlowException e(SourceName().c_str(), error);
         throw e;
     }
     if (input->getWidth() != input2->getWidth()) {
            char error[1024];
            sprintf(error, "%s: heights must match: %d, %d", SourceName().c_str(), input->getHeight(), input2->getHeight());
            DataFlowException e(SourceName().c_str(), error);
            throw e;
     }
     int new_height = input->getHeight() + input2->getHeight();
     image->ResetSize(input->getWidth(), new_height);
     Pixel* out_pix = image->getPixel();
     Pixel* in_pix1 = input->getPixel();
     Pixel* in_pix2 = input2->getPixel();

     for (int i=0; i<image->getWidth()*image->getHeight(); i++)
     {
          int row = i/image->getWidth();
          int col = i-(row*image->getWidth());
          if (row < input->getHeight())
          {
               int l = col + (row*input->getWidth());
               out_pix[i].r = in_pix1[l].r;
               out_pix[i].g = in_pix1[l].g;
               out_pix[i].b = in_pix1[l].b;
           } else {
               int r = col + ((row-input->getHeight())* (input2->getWidth()));
               out_pix[i].r = in_pix2[r].r;
               out_pix[i].g = in_pix2[r].g;
               out_pix[i].b = in_pix2[r].b;

          }
     }
}

Blender::Blender(void)
{
     this->factor = new double;
}

std::string Blender::SourceName() {
     return "Blender";
}

Blender::~Blender()
{
     delete factor;
}

void Blender::SetFactor(double factor)
{
     this->factor = new double(factor);
}

void Blender::Execute()
{    if (!input) {
         char error[1024];
         sprintf(error, "%s: no input 1!", SourceName().c_str());
         DataFlowException e(SourceName().c_str(), error);
         throw e;
     }
     if (!input2) {
          char error[1024];
          sprintf(error, "%s: no input 2!", SourceName().c_str());
          DataFlowException e(SourceName().c_str(), error);
          throw e;
      }
      if (!factor) {
          char error[1024];
          sprintf(error, "No factor set for Blender");
          DataFlowException e(SourceName().c_str(), error);
          throw e;
      }
     if ((*factor >= 1) || (*factor < 0)) {
          char error[1024];
          sprintf(error, "Invalid factor for Blender: %f", *factor);
          DataFlowException e(SourceName().c_str(), error);
          throw e;
     }
     if (input->getWidth() != input2->getWidth()) {
            char error[1024];
            sprintf(error, "%s: heights must match: %d, %d", SourceName().c_str(), input->getHeight(), input2->getHeight());
            DataFlowException e(SourceName().c_str(), error);
            throw e;
     }
     if (input->getHeight() != input2->getHeight()) {
             char error[1024];
             sprintf(error, "%s: heights must match: %d, %d", SourceName().c_str(), input->getHeight(), input2->getHeight());
             DataFlowException e(SourceName().c_str(), error);
             throw e;
     }
     image->ResetSize(input->getWidth(), input->getHeight());
     Pixel* out_pix = image->getPixel();
     double opp_fac = 1 - *(this->factor);
     Pixel* in_pix1 = input->getPixel();
     Pixel* in_pix2 = input2->getPixel();

     for (int i=0; i<image->getWidth()*image->getHeight(); i++)
     {
          unsigned char r_val = (*factor * in_pix1[i].r) + (opp_fac * in_pix2[i].r);
          unsigned char g_val = (*factor * in_pix1[i].g) + (opp_fac * in_pix2[i].g);
          unsigned char b_val = (*factor * in_pix1[i].b) + (opp_fac * in_pix2[i].b);
          out_pix[i].r = r_val;
          out_pix[i].g = g_val;
          out_pix[i].b = b_val;
  }
}

Color::Color(int width, int height, unsigned char r, unsigned char g, unsigned char b) {
     this->image = new Image();
     image->ResetSize(width, height);
     image->setSource(this);
     this->r = r;
     this->g = g;
     this->b = b;
}

void Color::Execute() {
     int i;
     Pixel* pixel = this->image->getPixel();
     for (i=0; i < this->image->getHeight()*this->image->getWidth(); i++) {
          pixel[i].r = this->r;
          pixel[i].g = this->g;
          pixel[i].b = this->b;
     }
}

std::string Color::SourceName() {
     return "Color";
}

void CheckSum::OutputCheckSum(std::string filename) {
     if (input) {
          Pixel* pixel = input->getPixel();
          unsigned char redCount=0, greenCount=0, blueCount=0;
          int i;
          for (i=0;i<input->getHeight()*input->getWidth();i++) {
               redCount += pixel[i].r;
               greenCount += pixel[i].g;
               blueCount += pixel[i].b;
          }
          FILE *outFile = fopen(filename.c_str(), "w");
          fprintf(outFile, "CHECKSUM: %d, %d, %d\n", redCount, greenCount, blueCount);
          fclose(outFile);
     }
}
