#ifndef VOCODER_H
#define VOCODER_H

#include <vector>
#include "utils.h"
#include "fft.h"
using namespace std;
class Vocoder
{
private:
    inline static vector<double> lastPhase;
    inline static vector<double> phaseSum;

public:
    /**
     * @param samples audio samples
     * @param shiftFactor time stretch or compression factor
     */
    static vector<double> timeShift(vector<double> samples, double shiftFactor, bool first)
    {
        int N = Utils::nextPowerOfTwo(samples.size());
        int delta = (int) round(shiftFactor * 44100);
        FFT handler = FFT(N);
        vector<double> output(samples.size() * shiftFactor);
        vector<complex<double>> out = handler.fft(samples);

        for (int i = 0; i < N; i++)
        {

        }

        // if (first)
        // {
        //     lastPhase.resize(N);
        //     phaseSum.resize(N);
        //     for (int i = 0; i < N; i++)
        //     {
        //         lastPhase[i] = atan2(out[i].imag(), out[i].real());
        //         phaseSum[i] = 0.0;
        //     }
        //     return samples;
        // }

        // for (int i = 0; i < N; i++)
        // {
        //     double phase = atan2(out[i].imag(), out[i].real());
        //     double phaseDif = phase - lastPhase[i];
        //     phaseDif -= round(phaseDif / (2 * M_PI)) * (2 * M_PI);
        //     phaseDif *= shiftFactor;
        //     phaseSum[i] += phaseDif;
        //     double newPhase = phaseSum[i];
        //     double magnitude = sqrt((out[i].real() * out[i].real()) + (out[i].imag() * out[i].imag()));
        //     out[i] = complex(magnitude * cos(newPhase), magnitude * sin(newPhase));
        // }
        // output = handler.ifft(out);
        return output;
    }
};

#endif