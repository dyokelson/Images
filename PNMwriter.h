#include <sink.h>

class PNMwriter : public Sink
{
     
     public:
     PNMwriter(void);
     void Write(char *filename);

};
