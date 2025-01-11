#ifndef VOCODER_H
#define VOCODER_H

#include <vector>
#include "../../FFT/kiss_fft.h"
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
     * @param sr audio's original sample rate
     */
    static vector<double> timeShift(vector<double> samples, double shiftFactor, double sr, bool first)
    {
        int N = Utils::nextPowerOfTwo(samples.size());
        int delta = (int) round(shiftFactor * sr);
        FFT handler = FFT(N);
        vector<double> output(samples.size());
        cpx* out = handler.fft(samples);

        if (first)
        {
            lastPhase.resize(N);
            phaseSum.resize(N);
            for (int i = 0; i < N; i++)
            {
                lastPhase[i] = atan2(out[i].i, out[i].r);
                phaseSum[i] = 0.0;
            }
            return samples;
        }

        for (int i = 0; i < N; i++)
        {
            double phase = atan2(out[i].i, out[i].r);
            double phaseDif = phase - lastPhase[i];
            phaseDif -= round(phaseDif / (2 * M_PI)) * (2 * M_PI);
            phaseDif *= shiftFactor;
            phaseSum[i] += phaseDif;
            double newPhase = phaseSum[i];
            double magnitude = sqrt((out[i].r * out[i].r) + (out[i].i * out[i].i));
            out[i].r = magnitude * cos(newPhase);
            out[i].i = magnitude * sin(newPhase);
        }
        output = handler.ifft(out);
        return output;
    }
};

#endif