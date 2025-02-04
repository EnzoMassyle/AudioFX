#include <../headers/convreverb.h>
#include <../headers/filters/lp.h>
unordered_map<string, string> Reverb::types = {
    {"CHURCH", "church.wav"},
    {"CAVE", "cave.wav"},
    {"AIRY", "airy.wav"}};

vector<vector<double>> Reverb::convReverb(vector<vector<double>> samples, string room)
{
    if (Reverb::types.find(room) == Reverb::types.end())
    {
        cout << room << " is not a valid type" << endl;
    }
    int numChannels = samples.size();
    SF_INFO irInfo;
    // string outFile = "../samples/ir/" + Reverb::types.at(room);
    string outFile = "../samples/ir/nuke.mp3";

    FileHandler fh = FileHandler();
    vector<double> irSamples = fh.open(outFile.c_str())[0];
    vector<thread> threads;
    vector<vector<double>> output(numChannels, vector<double>(samples[0].size(), 0.0));
    int sizes[numChannels];
    for (int chan = 0; chan < numChannels; chan++)
    {
        sizes[chan] = samples[chan].size();
        // threads.emplace_back(Utils::convolve, ref(samples[chan]), irSamples);
        threads.emplace_back(convolveChannel, samples[chan], irSamples, ref(output[chan]));
    }

    for (thread &t : threads)
    {
        t.join();
    }

    // for (int chan = 0; chan < numChannels; chan++)
    // {
    //     samples[chan].resize(sizes[chan]);
    // }
    LowPass lp = LowPass(0.3);
    lp.process(output);
    Utils::normalize(output);
    return output;
}

void Reverb::convolveChannel(vector<double> channel, vector<double> irSamples, vector<double>& out)
{
    // int step = PITCH_CHUNK_SZ / NUM_OVERLAP;
    // vector<thread> threads;
    // random_device device;
    // mt19937 gen(device());
    // uniform_int_distribution grainStart(-PITCH_OFFSET,PITCH_OFFSET);
    // uniform_int_distribution grainSize(PITCH_CHUNK_SZ,PITCH_CHUNK_SZ + 2000);
    int step = CHUNK_SIZE / 3;
    vector<thread> threads;
    for (int start = 0 ; start < channel.size(); start += step)
    {
        // int randStart = max(0, start + grainStart(gen));
        // int randEnd = grainSize(gen) + randStart;
        // if (randEnd >= channel.size()) {
        //     continue;
        // }
        int end = start + CHUNK_SIZE;
        if (end >= channel.size()) {
            continue;
        }
        vector<double> slice(channel.begin() + start, channel.begin() + end);
        Utils::applyWindow(slice);
        threads.emplace_back([slice, irSamples, start, &out]() {
            // cout << "convolving slice" << endl;
            int originalSize = slice.size();
            vector<double> output = Utils::convolve(slice, irSamples);
            // slice.resize(originalSize);
            output.resize(originalSize);
            for (int i = 0; i < slice.size(); i++) {
                if (i + start < out.size()) {
                    out[i + start] += output[i];
                }

            }
        });
    }

    for (thread &t : threads)
    {
        t.join();
    }
}
