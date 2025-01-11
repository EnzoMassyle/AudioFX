#ifndef FFT_H
#define FFT_H

#include "../../FFT/kiss_fft.h"
#include <vector>
using namespace std;
typedef kiss_fft_cpx cpx;

class FFT {
    private:
        kiss_fft_cfg cfg;
        kiss_fft_cfg inv;
        int n;
        cpx* in;
        cpx* out;

    public:
        FFT(int n);
        ~FFT();
        
        cpx* fft(vector<double> v);
        vector<double> ifft(cpx* c);
};

#endif 