#ifndef FFT_H
#define FFT_H

#include <vector>
#include <fftw3.h>
#include <complex>
using namespace std;
typedef fftw_complex cpx;

class FFT {
    private:
        int n;
        cpx* f;
        fftw_plan forward;
        fftw_plan backward;

    public:
        FFT(int n);
        ~FFT();
        
        vector<complex<double>> fft(vector<double> v);
        vector<double> ifft(vector<complex<double>> c);
};

#endif 