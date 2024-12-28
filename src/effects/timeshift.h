#ifndef TIMESHIFT_H
#define TIMESHIFT_H

#include<iostream>
#include<vector>
#include<sndfile.h>

using namespace std;
class TimeShift {
  public: 
    static void process(const char* fn, double shiftFactor) {
      const char* inFileName = fn;
      const char* outFileName = "out.wav";
      // Prepare to read wav file
      SNDFILE* inFile;
      SNDFILE* outFile;
      SF_INFO info;
      memset(&info, 0, sizeof(info));
      try {
          if (!(inFile = sf_open(inFileName, SFM_READ, &info))) {
              throw inFileName;
          }
          if (!(outFile = sf_open(outFileName, SFM_WRITE, &info))) {
              throw outFileName;
          }
      } catch (string& fn) {
          cout << fn << " not found" << endl; 
      }

      

    }
};

#endif