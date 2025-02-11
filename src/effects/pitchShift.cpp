
#include <../headers/pitchshift.h>
#include <vocoder.h>
#include <fft.h>
#include <valarray>
#include <afx.h> 

vector<vector<double>> PitchShift::changePitch(vector<vector<double>> samples, double pitchFactor)
{
    AFX afx = AFX();
    samples = afx.changeTempo(samples, 1.0 / pitchFactor); // First resample to change pitch
    int numChannels = samples.size();
    vector<vector<double>> output(numChannels, vector<double>(samples[0].size() / pitchFactor, 0.0));
    cout << "here" << endl;
    vector<thread> threads;

    // Rescale each channel back to original time
    for (int chan = 0; chan < numChannels; chan++)
    {
        threads.emplace_back(shiftChannel, samples[chan], pitchFactor, ref(output[chan]));
    }

    for (thread &t : threads)
    {
        t.join();
    }
    Utils::normalize(output);
    return output;
}

void PitchShift::shiftChannel(vector<double> channel, double pitchFactor, vector<double> &out)
{
    int step = PITCH_CHUNK_SZ / 4;
    // vector<thread> threads;
    int frameSize = 5000;
    int hopSize = 2000;
    int n = round(((channel.size()) / hopSize) + 1);
    vector<vector<complex<double>>> stft(n, vector<complex<double>>(frameSize));

    FFT handler = FFT(Utils::nextPowerOfTwo(frameSize));
    for (int start = 0, j = 0; start < channel.size(); start += hopSize, j++)
    {
        int end = min(start + frameSize, (int)channel.size() - 1);

        vector<double> slice(channel.begin() + start, channel.begin() + end);
        Utils::applyWindow(slice);
        stft[j] = handler.fft(slice);

        // threads.emplace_back(resampleSlice, channel, slice, start, pitchFactor, ref(out));
        // slice = Vocoder::timeShift(slice, pitchFactor, start == 0);
        // Utils::applyWindow(slice);
        // for (int i = 0; i < slice.size(); i++)
        // {
        //     out[start + i] += slice[i];
        // }
    }
    cout << "allocated stft" << endl;
    int newN = round(n / pitchFactor);
    vector<vector<complex<double>>> stftN(newN, vector<complex<double>>(stft[0].size()));
    for (int i = 0; i < newN; i++)
    {
        double og = i * pitchFactor;
        int low = (floor(og) < n) ? floor(og) : n - 1;
        int high = (ceil(og) < n) ? ceil(og) : n - 1;
        double alpha = og - low;


        stftN[i] = Utils::addComplex(Utils::scaleComplex(stft[low], 1 - alpha), Utils::scaleComplex(stft[high], alpha)); //(stft[low] * (1-alpha)) + (stft[high] * alpha);
    }

    cout << "performed interpolation" << endl;
    for (int start = 0, i = 0; start < out.size() && i < newN; start += hopSize, i++)
    {
        vector<double> inverse = handler.ifft(stftN[i]);
        Utils::applyWindow(inverse);
        for (int j = 0; j < inverse.size() && j + start < out.size(); j++)
        {
            out[j + start] += inverse[j];
        }
    }

    // for (thread &t : threads)
    // {
    //     t.join();
    // }
}

// void PitchShift::resampleSlice(vector<double> samples, vector<double> slice, int start, double pitchFactor, vector<double> &out)
// {
//     int resampledSize = slice.size() * pitchFactor;  // Scale slice size by pitch
//     // vector<double> resampled(resampledSize, 0.0);
//     vector<double> window = Utils::generateWindow(slice.size());  // Window matches grain size

//     for (int i = 0; i < resampledSize; i++)
//     {

//         // double newIdx = (i * pitchFactor) + start;  // Compute correct fractional position
//         // // **Lagrange Interpolation**
//         // double interpolatedSample = Utils::lagrangeInterpolate(samples, newIdx);

//         // // **Apply Grain Windowing**
//         // resampled[i] = interpolatedSample * window[i % window.size()];

//     }

//     // **Accumulate Resampled Data into Output Buffer**
//     for (int i = 0; i < resampledSize; i++)
//     {
//         out[start + i] += resampled[i];
//     }

// }