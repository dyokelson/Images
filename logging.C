#include <logging.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

FILE *Logger::logger = fopen("logger","w");

void Logger::LogEvent(const char *event) {
     fwrite(event, strlen(event), 1, logger);
     fwrite("\n", sizeof(char), 1, logger);
}

void Logger::Finalize() {

     fclose(logger);
}

DataFlowException::DataFlowException(const char *type, const char *error) {
     sprintf(msg,"Throwing exception: (%s): %s", type, error);
     Logger::LogEvent(msg);
}
