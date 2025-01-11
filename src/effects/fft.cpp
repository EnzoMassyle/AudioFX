#include "fft.h"
FFT::FFT(int n) {
    this->n = n;
    cfg = kiss_fft_alloc(n, 0, nullptr, nullptr);
    inv = kiss_fft_alloc(n, 1, nullptr, nullptr);
    if (!cfg || !inv)
    {
        kiss_fft_free(cfg);
        kiss_fft_free(inv);
        throw "allocation failed";
    }
}

FFT::~FFT() {
    kiss_fft_free(cfg);
    kiss_fft_free(inv);
    delete in;
    delete out;
}

cpx* FFT::fft(vector<double> v) {
    in = new cpx[n];
    out = new cpx[n];
    for (int i = 0; i < n ; i++) {
        in[i].r = i < v.size() ? v[i] : 0.0;
        in[i].i = 0;
    }
    kiss_fft(cfg, in, out);
    return out;
}

vector<double> FFT::ifft(cpx* c) {
    vector<double> res(n);
    kiss_fft(inv, c, out);
    for (int i = 0; i < n; i++)
    {
        res[i] = out[i].r / n;
    }
    return res;
}