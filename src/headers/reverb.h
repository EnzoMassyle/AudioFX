#ifndef REVERB_H
#define REVERB_H

#include <iostream>
#include <vector>
#include <sndfile.h>
#include "filehandler.h"
#include "utils.h"
#include <thread>
#include <future>
#include <unordered_map>
#include <string>
class Reverb
{
private:
    static unordered_map<string, string> types;

public:
    static void convReverb(const char *fn, string t = "CHURCH");

};

#endif