#include <PNMreader.h>
#include <image.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <logging.h>

PNMreader::PNMreader(char* filename)
{
     this->filename = new char[strlen(filename)];
     strcpy(this->filename, filename);
}

PNMreader::~PNMreader()
{
     delete [] filename;
}

std::string PNMreader::SourceName() {
     return "PNMreader";
}

void PNMreader::Execute()
{
     FILE *f_in = fopen(filename, "r");
     if (!f_in) {
         char error[1024];
         sprintf(error, "%s: No file found with name: %s", SourceName().c_str(), filename);
         DataFlowException e(SourceName().c_str(), error);
         throw e;
     }
     char magicNum[128];
     int width, height, maxval;
     fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);

     image->ResetSize(width, height);
     fread(image->getPixel(), sizeof(Pixel), width*height, f_in);

     fclose(f_in);
}
