#include <source.h>
#include <sink.h>
#include <string>

class Filter : public Source, public Sink
{
     public:
     Filter(void);
     virtual void Update();
};

class Mirror : public Filter {

     public:
     Mirror(void);
     void Execute();
     virtual std::string SourceName();
};

class Rotate : public Filter {

     public:
     Rotate(void);
     void Execute();
     virtual std::string SourceName();
};

class Subtract : public Filter {

     public:
     Subtract(void);
     void Execute();
     virtual std::string SourceName();
};

class Grayscale : public Filter {

     public:
     Grayscale(void);
     void Execute();
     virtual std::string SourceName();
};

class Blur : public Filter {

     public:
     Blur(void);
     void Execute();
     virtual std::string SourceName();
};

class Color : public Source {
     protected:
     virtual void Execute();
     unsigned char r,g,b;

     public:
     Color(int width, int height, unsigned char r, unsigned char g, unsigned char b);
     virtual std::string SourceName();
};

class Shrinker : public Filter
{
     public:
     Shrinker(void);
     void Execute();
     virtual std::string SourceName();
};

class LRCombine : public Filter
{
     public:
     LRCombine(void);
     void Execute();
     virtual std::string SourceName();
};

class TBCombine : public Filter
{
     public:
     TBCombine(void);
     void Execute();
     virtual std::string SourceName();
};

class Blender : public Filter
{
     double* factor;

     public:
     Blender(void);
    ~Blender();
     void Execute();
     void SetFactor(double factor);
     virtual std::string SourceName();
};

class CheckSum : public Sink {

     public:
     void OutputCheckSum(std::string filename);
};
