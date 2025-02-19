#include <../headers/tempo.h>
#include <mutex> 

mutex m;
int Tempo::sliceSize = 750000;
vector<vector<double>> Tempo::changeTempo(vector<vector<double>> samples, double r)
{
    int numChannels = samples.size();
    int channelLength = samples[0].size();
    int newChannelLength = channelLength / r;
    vector<vector<double>> output(numChannels, vector<double>(newChannelLength, 0.0));
    vector<thread> threads;
    vector<double> window = Utils::generateWindow(32);
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
    int newChannelLength = channel.size() / r;
    vector<thread> threads;
    for (int i = 0; i < newChannelLength; i += Tempo::sliceSize)
    {
        threads.emplace_back(changeTempoSlice, channel, i, r, ref(out));
    }

    for (thread &t : threads)
    {
        t.join();
    }
}

void Tempo::changeTempoSlice(const vector<double>& channel, int sliceStart, double r, vector<double> &out)
{
    vector<double> window = Utils::generateWindow(32);
    for (int i = sliceStart; i < sliceStart + Tempo::sliceSize; i++)
    {
        if (i >= out.size()) break;
        double center = i * r;
        for (int j = max((int)center - 16, 0), k = 0; j < min((int)center + 16, (int)channel.size()); j++, k++)
        {
            out[i] += channel[j] * Utils::sinc(center - j) * window[k];
        }
    }
}