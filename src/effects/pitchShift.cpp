
#include <../headers/pitchshift.h>

vector<vector<double>> PitchShift::changePitch(vector<vector<double>> samples, double pitchFactor)
{

    int numChannels = samples.size();
    vector<vector<double>> output(numChannels, vector<double>(samples[0].size(), 0.0));
    vector<thread> threads;

    for (int chan = 0; chan < numChannels; chan++)
    {
        threads.emplace_back(shiftChannel, samples[chan], pitchFactor, ref(output[chan]));
    }

    for (thread &t : threads)
    {
        t.join();
    }
    return output;
}

void PitchShift::shiftChannel(vector<double> channel, double pitchFactor, vector<double> &out)
{
    int step = PITCH_CHUNK_SZ / (NUM_OVERLAP / pitchFactor) ;
    vector<thread> threads;
    random_device device;
    mt19937 gen(device());
    uniform_int_distribution grainStart(-PITCH_OFFSET, PITCH_OFFSET);
    uniform_int_distribution grainSize(PITCH_CHUNK_SZ, PITCH_CHUNK_SZ + 2000);
    for (int start = 0; start < channel.size(); start += step)
    {
        int randStart = max(0, start + grainStart(gen));
        int randEnd = grainSize(gen) + randStart;
        if (randEnd >= channel.size())
        {
            continue;
        }
        vector<double> slice(channel.begin() + randStart, channel.begin() + randEnd);
        Utils::applyWindow(slice);
        threads.emplace_back(resampleSlice, channel, slice, start, pitchFactor, ref(out));
    }

    for (thread &t : threads)
    {
        t.join();
    }
}


void PitchShift::resampleSlice(vector<double> samples, vector<double> slice, int start, double pitchFactor, vector<double> &out)
{
    int resampledSize = slice.size() * pitchFactor;  // Scale slice size by pitch
    vector<double> resampled(resampledSize, 0.0);
    vector<double> window = Utils::generateWindow(slice.size());  // Window matches grain size

    for (int i = 0; i < resampledSize; i++)
    {
        double newIdx = (i * pitchFactor) + start;  // Compute correct fractional position
        // **Lagrange Interpolation**
        double interpolatedSample = Utils::lagrangeInterpolate(samples, newIdx);

        // **Apply Grain Windowing**
        resampled[i] = interpolatedSample * window[i % window.size()];
    }

    // **Accumulate Resampled Data into Output Buffer**
    for (int i = 0; i < resampledSize; i++)
    {
        out[start + i] += resampled[i];

    }

}