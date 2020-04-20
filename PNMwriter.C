#include <PNMwriter.h>
#include <image.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

PNMwriter::PNMwriter(void)
{
}

void PNMwriter::Write(char *filename)
{
     FILE *f_out = fopen(filename, "w");
     fprintf(f_out, "%s\n%d %d\n%d\n", "P6", input->getWidth(), input->getHeight(), 255);
     fwrite(input->getPixel(), sizeof(Pixel), input->getWidth()*input->getHeight(), f_out);

     fclose(f_out);
}
