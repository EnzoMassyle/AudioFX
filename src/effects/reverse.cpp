#include <../headers/reverse.h>

void Reverse::reverse(const char *fn)
{
    SF_INFO info;
    vector<vector<double>> samples = FileHandler::open(fn, info);

    for (int chan = 0; chan < samples.size(); chan++) {
        std::reverse(samples[chan].begin(), samples[chan].end());
    }

    FileHandler::write(samples, info);
}