#ifndef FFT_H
#define FFT_H

#include <vector>
#include <fftw3.h>
#include <complex>
#include <thread>
#include <mutex>
using namespace std;
typedef fftw_complex cpx;


/**
 * @class FFT
 * @brief Handler class to perform the Fast Fourier Transform
 * 
 */
class FFT
{
private:
    int n;
    cpx *f;
    static fftw_plan forward;
    static fftw_plan backward;

    // these vars are needed for multi-threading
    static cpx *dummy;
    static mutex m;
    
public:
    static bool planExists;
    /**
     * @brief Allocate FFT plans and buffers , enabled for multi-threaded or serial use
     * @param n -> FFT size
     */
    FFT(int n);

    /**
     * @brief Destroy FFT plans and buffers
     */
    ~FFT();

    /**
     * @brief Apply FFT to vector v
     * @param v -> vector
     */
    vector<complex<double>> fft(const vector<double> &v);

    /**
     * @brief Apply IFFT to complex vector c
     * @param c -> complex vector
     */
    vector<double> ifft(const vector<complex<double>> &c);

    /**
     * @brief Associated with constructor. Will only be called once per the scope of the FFT object instantiation. Needed for multi-threading
     * @param n -> FFT size
     */
    static void preInit(int n);

    /**
     * @brief Destroy plans once all FFT objects are out of scope. Needed for multi-threading
     */
    static void destroyPlan();
};

#endif