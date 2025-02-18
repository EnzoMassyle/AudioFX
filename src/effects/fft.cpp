#include "../headers/fft.h"
#include <iostream>

fftw_plan FFT::forward;
fftw_plan FFT::backward;
cpx* FFT::dummy;
once_flag FFT::flag;
shared_ptr<void> FFT::plan;

void FFT::preInit(int n) {
    FFT::dummy = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);
    FFT::forward = fftw_plan_dft_1d(n, FFT::dummy, FFT::dummy, FFTW_FORWARD, FFTW_ESTIMATE);
    FFT::backward = fftw_plan_dft_1d(n, FFT::dummy, FFT::dummy, FFTW_BACKWARD, FFTW_ESTIMATE);
    plan = shared_ptr<void>(nullptr, [](void*) {destroyPlan();});
}

void FFT::destroyPlan() {
    fftw_destroy_plan(FFT::forward);
    fftw_destroy_plan(FFT::backward);
    fftw_free(dummy);
}

FFT::FFT(int n) {
    this->n = n; 
    call_once(flag, preInit, n);
    f = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);
}

FFT::~FFT() {
    fftw_free(f);
}

vector<complex<double>> FFT::fft(vector<double> v) {
    for (int i = 0; i < n ; i++) {
        f[i][0] = i < v.size() ? v[i] : 0.0;
        f[i][1] = 0;
    }
    // cout << "before " << endl;
    fftw_execute_dft(FFT::forward, f, f);
    // cout << "after" << endl;

    vector<complex<double>> res(n);
    for (int i = 0; i < n; i++) {
        // cout << i << " " << f << endl;
        res[i] = complex<double>(f[i][0], f[i][1]);
    }

    return res;
}

vector<double> FFT::ifft(vector<complex<double>> c) {
    vector<double> res(n);
    for (int i = 0; i < n ; i++) {
        f[i][0] = i < c.size() ? c[i].real() : 0.0;
        f[i][1] = i < c.size() ? c[i].imag() : 0.0;
    }
    fftw_execute_dft(FFT::backward, f, f);
    for (int i = 0; i < n; i++)
    {
        res[i] = f[i][0];
    }
    return res;
}