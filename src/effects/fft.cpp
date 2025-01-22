#include "fft.h"
FFT::FFT(int n) {
    this->n = n;
    f = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);
    // out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);   
}

FFT::~FFT() {
    fftw_free(f);
    // fftw_free(out);
}

vector<complex<double>> FFT::fft(vector<double> v) {
    for (int i = 0; i < n ; i++) {
        f[i][0] = i < v.size() ? v[i] : 0.0;
        f[i][1] = 0;
    }
    forward = fftw_plan_dft_1d(n, f, f, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(forward);
    vector<complex<double>> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = complex<double>(f[i][0], f[i][1]);
    }
    fftw_destroy_plan(forward);
    return res;
}

vector<double> FFT::ifft(vector<complex<double>> c) {
    vector<double> res(n);
    for (int i = 0; i < n ; i++) {
        f[i][0] = i < c.size() ? c[i].real() : 0.0;
        f[i][1] = i < c.size() ? c[i].imag() : 0.0;
    }

    backward = fftw_plan_dft_1d(n, f, f, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(backward);
    for (int i = 0; i < n; i++)
    {
        res[i] = f[i][0] / n;
    }
    fftw_destroy_plan(backward);
    return res;
}