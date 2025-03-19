#include "../../include/tempo.h"

vector<vector<double>> Tempo::changeTempo(const vector<vector<double>>& samples, double r)
{
    if (samples.size() == 0) {
        throw "Must have at least one channel of audio";
    }
    int numChannels = samples.size();
    int newChannelLength = samples[0].size()/ r;
    vector<vector<double>> output(numChannels, vector<double>(newChannelLength, 0.0));

    vector<thread> threads;
    for (int chan = 0; chan < numChannels; chan++)
    {
        threads.emplace_back(changeTempoChannel, samples[chan], r, ref(output[chan]));
    }

    for (thread &t : threads)
    {
        t.join();
    }
    return output;
}
void Tempo::changeTempoChannel(const vector<double>& channel, double r, vector<double> &out)
{
    int hopSize = channel.size() / (thread::hardware_concurrency() - 1);
    int newChannelLength = channel.size() / r;
    vector<thread> threads;
    for (int i = 0; i < newChannelLength; i += hopSize)
    {
        threads.emplace_back(changeTempoFrame, channel, i, hopSize, r, ref(out));
    }

    for (thread &t : threads)
    {
        t.join();
    }
}

void Tempo::changeTempoFrame(const vector<double>& channel, int frameStart, int frameSize, double r, vector<double> &out)
{
    vector<double> window = Utils::generateWindow(32);
    for (int i = frameStart; i < frameStart + frameSize && i < out.size(); i++)
    {
        double center = i * r;
        for (int j = max((int)center - 16, 0), k = 0; j < min((int)center + 16, (int)channel.size()); j++, k++)
        {
            out[i] += channel[j] * Utils::sinc(center - j) * window[k];
        }
    }
}

vector<double> Tempo::changeTempo(const vector<double>& samples, double r)
{
    vector<double> out(samples.size(), 0.0);
    int hopSize = samples.size() / (thread::hardware_concurrency() - 1);
    int newChannelLength = samples.size() / r;
    vector<thread> threads;
    for (int i = 0; i < newChannelLength; i += hopSize)
    {
        threads.emplace_back(changeTempoFrame, samples, i, hopSize, r, ref(out));
    }

    for (thread &t : threads)
    {
        t.join();
    }
    
    return out;
}