#ifndef FFT_H
#define FFT_H

#include <vector>
#include <fftw3.h>
#include <complex>
#include <thread>
using namespace std;
typedef fftw_complex cpx;

class FFT
{
private:
    int n;
    cpx *f;
    static fftw_plan forward;
    static fftw_plan backward;

    // these vars are needed for multi-threading
    static cpx *dummy;
    static once_flag flag;
    static shared_ptr<void> plan;

public:
    /**
     * @param n -> FFT size
     *
     * Allocate FFT plans and buffers , enabled for multi-threaded or serial use
     */
    FFT(int n);

    /**
     * Destroy FFT plans and buffers
     */
    ~FFT();

    /**
     * @param v -> vector
     *
     * Apply FFT to vector v
     */
    vector<complex<double>> fft(const vector<double> &v);

    /**
     * @param c -> complex vector
     *
     * Apply IFFT to complex vector c
     */
    vector<double> ifft(const vector<complex<double>> &c);

    /**
     * @param n -> FFT size
     *
     * Associated with constructor. Will only be called once per the scope of the FFT object instantiation. Needed for multi-threading
     */
    static void preInit(int n);

    /**
     * Destroy plans once all FFT objects are out of scope. Needed for multi-threading
     */
    static void destroyPlan();
};

#endif