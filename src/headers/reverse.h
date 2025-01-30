#ifndef REVERSE_H
#define REVERSE_H
#include <sndfile.h> 
#include <vector> 
#include <filehandler.h>


class Reverse {
    public:
        static void reverse(const char* fn);
};
#endif