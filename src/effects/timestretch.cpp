#include "../../include/timestretch.h"

vector<vector<double>> TimeStretch::changeSpeed(const vector<vector<double>>& samples, double shiftFactor)
{
    if (shiftFactor <= 0) {
        throw "Shift factor must be greater than 0";
    }
    if (samples.size() == 0) {
        throw "Must have at least one channel of audio";
    }
    int numChannels = samples.size();
    int channelLength = samples[0].size();

    vector<vector<double>> output(numChannels, vector<double>(channelLength / shiftFactor, 0.0));
    vector<thread> threads;

    // Process each channel independently
    for (int chan = 0; chan < numChannels; chan++)
    {
        threads.emplace_back(stretchChannel, samples[chan], shiftFactor, ref(output[chan]));
    }

    for (thread &t : threads)
    {
        t.join();
    }
    Utils::normalize(output);
    if (FFT::planExists)
    {
        FFT::destroyPlan();
    }
    return output;
}



void TimeStretch::stretchChannel(const vector<double> &channel, double shiftFactor, vector<double> &out)
{
    vector<thread> threads;
    int hopSize = channel.size() / (thread::hardware_concurrency() - 1);
    for (int i = 0, j = 0; i < channel.size(); i += hopSize, j++)
    {
        int end = min(i + hopSize, (int)channel.size());
        int start = max(0, i - 2000); // Ensure smooth overlap when parallel processing
        vector<double> slice(channel.begin() + start, channel.begin() + end);

        threads.emplace_back(stretchFrame, slice, start / shiftFactor, shiftFactor, ref(out));
    }

    for (thread &t : threads)
    {
        t.join();
    }
}
void TimeStretch::stretchFrame(const vector<double> &frame, int shiftedStart, double shiftFactor, vector<double> &out)
{
    int n = round(((frame.size()) / HOP_SZ) + 1);
    vector<vector<complex<double>>> stftBins(n, vector<complex<double>>(FRAME_SZ));

    FFT handler = FFT(Utils::nextPowerOfTwo(FRAME_SZ));

    for (int start = 0, j = 0; start < frame.size() && j < n; start += HOP_SZ, j++)
    {
        int end = min(start + FRAME_SZ, (int)frame.size());
        vector<double> slice(frame.begin() + start, frame.begin() + end);
        Utils::applyWindow(slice);
        stftBins[j] = handler.fft(slice);
    }

    int newBinCnt = round(n / shiftFactor);
    vector<vector<complex<double>>> newStftBins(newBinCnt, vector<complex<double>>(FRAME_SZ));
    vector<double> phaseSum(FRAME_SZ, 0.0);

    for (int i = 0; i < newBinCnt; i++)
    {
        double og = i * shiftFactor;
        int low = (floor(og) < n) ? floor(og) : n - 1;
        int high = (ceil(og) < n) ? ceil(og) : n - 1;
        double alpha = og - low;

        newStftBins[i] = Utils::addComplex(Utils::scaleComplex(stftBins[low], 1 - alpha), Utils::scaleComplex(stftBins[high], alpha));

        /* Ensure phase coherence */
        for (int j = 0; j < FRAME_SZ; j++)
        {
            double phaseDiff = arg(newStftBins[i][j]);
            double lastPhase = 0.0;
            double lastMagnitude = 0.0;

            if (i > 0)
            {
                lastPhase = arg(newStftBins[i - 1][j]);
                lastMagnitude = abs(newStftBins[i - 1][j]);
                phaseDiff -= lastPhase;
            }

            /* Transient detection, if transient, do nothing to keep timbre */
            if (abs(newStftBins[i][j]) <= 2.0 * lastMagnitude)
            {
                /* Perform phase unwrapping */
                while (phaseDiff > PI)
                    phaseDiff -= 2 * PI;
                while (phaseDiff < -PI)
                    phaseDiff += 2 * PI;

                phaseSum[j] += phaseDiff;

                newStftBins[i][j] = polar(abs(newStftBins[i][j]), phaseSum[j]);
            }
        }
    }
    for (int start = 0, i = 0; i < newBinCnt; start += HOP_SZ, i++)
    {
        vector<double> inverse = handler.ifft(newStftBins[i]);
        Utils::applyWindow(inverse);
        for (int j = 0; j < inverse.size() && j + shiftedStart + start < out.size(); j++)
        {
            out[j + shiftedStart + start] += inverse[j];
        }
    }
}
