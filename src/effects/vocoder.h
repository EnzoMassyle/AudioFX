#ifndef VOCODER_H
#define VOCODER_H

#include <vector>
#include "../../FFT/kiss_fft.h"
#include "utils.h"
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
        vector<double> output(samples.size());
        kiss_fft_cfg cfg = kiss_fft_alloc(N, 0, nullptr, nullptr);
        kiss_fft_cfg inv = kiss_fft_alloc(N, 1, nullptr, nullptr);

        if (!cfg || !inv)
        {
            kiss_fft_free(cfg);
            kiss_fft_free(inv);
            throw "allocation failed";
        }
        kiss_fft_cpx *in = (kiss_fft_cpx *)malloc(sizeof(kiss_fft_cpx) * N);
        kiss_fft_cpx *out = (kiss_fft_cpx *)malloc(sizeof(kiss_fft_cpx) * N);
        for (int i = 0; i < N; i++)
        {
            in[i].r = i < samples.size() ? samples[i] : 0.0;
            in[i].i = 0;
        }

        kiss_fft(cfg, in, out);
        /* TODO Perform analysis */
        // This is BETA, refactor this in the future
        if (first)
        {
            lastPhase.resize(N);
            phaseSum.resize(N);

            for (int i = 0; i < N; i++)
            {
                lastPhase[i] = atan2(out[i].i, out[i].r);
                phaseSum[i] = 0.0;
            }
            free(in);
            free(out);
            kiss_fft_free(cfg);
            kiss_fft_free(inv);
            return samples;
        }

        /* Change this implementation to enact what a phase vocoder should actually do*/
        for (int i = 0; i < N; i++)
        {
            double phase = atan2(out[i].i, out[i].r);
            double phaseDif = phase - lastPhase[i];
            // if (phaseDif > M_PI) {
            //     phaseDif -= 2*M_PI;
            // } else if (phaseDif < -M_PI) {
            //     phaseDif += 2*M_PI;
            // }
            phaseDif -= round(phaseDif / (2 * M_PI)) * (2 * M_PI);
            phaseDif *= shiftFactor;
            phaseSum[i] += phaseDif;
            double newPhase = phaseSum[i];
            double magnitude = sqrt((out[i].r * out[i].r) + (out[i].i * out[i].i));
            out[i].r = magnitude * cos(newPhase);
            out[i].i = magnitude * sin(newPhase);
        }
        kiss_fft(inv, out, in);
        for (int i = 0; i < samples.size(); i++)
        {
            output[i] = in[i].r;
        }
        free(in);
        free(out);
        kiss_fft_free(cfg);
        kiss_fft_free(inv);
        return output;
    }
};

#endif