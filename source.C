#include <source.h>
#include <logging.h>

Source::Source(void)
{
     this->image = new Image();
     image->setSource(this);
}

Image* Source::GetOutput() {
     return this->image;
}

void Source::Update() {
     char msg[128];
     sprintf(msg, "%s: about to execute", SourceName().c_str());
     Logger::LogEvent(msg);
     Execute();
     sprintf(msg, "%s: done executing", SourceName().c_str());
     Logger::LogEvent(msg);
}
