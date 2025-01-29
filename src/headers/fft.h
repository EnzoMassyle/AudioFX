#ifndef FFT_H
#define FFT_H

#include <vector>
#include <fftw3.h>
#include <complex>
#include <thread>
#include <mutex>
using namespace std;
typedef fftw_complex cpx;

class FFT {
    private:
        int n;
        cpx* f;
        static fftw_plan forward;
        static fftw_plan backward;
        static cpx* dummy;
        static once_flag flag;
        static shared_ptr<void> plan;

    public:
        FFT(int n);
        ~FFT();
        vector<complex<double>> fft(vector<double> v);
        vector<double> ifft(vector<complex<double>> c);
        static void preInit(int n);
        static void destroyPlan();
};

#endif 