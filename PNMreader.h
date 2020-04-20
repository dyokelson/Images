#include <source.h>
#include <string>

class PNMreader : public Source 
{
     char* filename;

     public:
     PNMreader(char* filename);
    ~PNMreader();
     virtual void Execute();
     virtual std::string SourceName();
};
