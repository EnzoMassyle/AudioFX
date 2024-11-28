#include "autotune.h"

map<int, vector<double>> Autotune::noteTbl;
Autotune::Autotune(int intensity) {
    this->intensity = intensity;
    af.setNumChannels(1);
    af.setSampleRate(44100);
    st.setSampleRate(44100);
    st.setChannels(1);
}

void Autotune::process(const string& fn) {

    /* Load file for processing */
    cout << "Loading Audio File ... " << endl;
    try {
        if (!af.load(fn)) {
            throw fn;
        }
    } catch (string & fn) {
        cout << fn << " not found" << endl;
    }
    cout << "Success!" << endl;
    cout << "Processing Audio File..." << endl;
    int numSamples = af.getNumSamplesPerChannel();
    int paddedSize = ((numSamples + 512 - 1) / 512) * 512; // Round up to the nearest multiple of hop size
    af.samples[0].resize(paddedSize, 0); // Pad with zeros


    vector<double> window = generateWindow(512);

    for (int start = 0, end = 1024; end < numSamples; start += 512, end += 512) {
        vector<double> audioSlice(af.samples[0].begin() + start, af.samples[0].begin() + end);
        for (int i = 0; i < window.size(); i++) {
            audioSlice[i] *= window[i];
        }
        vector<double> shiftedSlice = findNearestNote(audioSlice);
        for (int i = start, j = 0; j < shiftedSlice.size() && i < end && i < af.samples[0].size(); i++, j++) {
            af.samples[0][i] += shiftedSlice[j];
        }
    }

    for (int i = 0; i < af.samples[0].size(); i++) {
        af.samples[0][i] *= 0.5;
    }


    cout << "Saving File..." << endl;
    af.save("test.wav");
}

vector<double> Autotune::findNearestNote(vector<double> slice) {

    int fftSize = 1024;
    kiss_fft_cfg cfg = kiss_fft_alloc(fftSize, 0, nullptr, nullptr);
    kiss_fft_cfg inv = kiss_fft_alloc(fftSize, 1, nullptr, nullptr);
    kiss_fft_cpx* in = (kiss_fft_cpx*) malloc(sizeof(kiss_fft_cpx) * fftSize);
    kiss_fft_cpx* out = (kiss_fft_cpx*) malloc(sizeof(kiss_fft_cpx) * fftSize);
    kiss_fft_cpx* shiftedOut = (kiss_fft_cpx*) malloc(sizeof(kiss_fft_cpx) * fftSize);

    for (int i = 0; i < fftSize; i++) {
        in[i].r = slice[i];
        in[i].i = 0;
        shiftedOut[i].r = 0;
        shiftedOut[i].i = 0;
    }

    kiss_fft(cfg, in, out);

    // Find dominating frequency
    double maxMag = 0;
    int dominatingBin = 0;
    for (int i = 0; i < fftSize; i++) {
        double magnitude = sqrt((out[i].r * out[i].r) + (out[i].i * out[i].i));
        if (magnitude > maxMag) {
            maxMag = magnitude;
            dominatingBin = i;
        }
    }

    double dominatingFrequency = (dominatingBin * af.getSampleRate()) / fftSize;
    double shiftFactor = findShiftingFactor(dominatingFrequency);
    if (shiftFactor == 0) {
        free(in);
        free(out);
        free(shiftedOut);
        kiss_fft_free(cfg);
        kiss_fft_free(inv);
        return slice;
    }



    // Apply shifting factor
    for (int i = 0; i < fftSize; i++) {
        int newBin = (int) i * shiftFactor;
        if (newBin < fftSize / 2) {
            shiftedOut[newBin].r += out[i].r;
            shiftedOut[newBin].i += out[i].i;
        }
    }
    double lowCutoff = 80.0;
    double highCutoff = 5000.0;

    int  highCutoffBin = (int) (highCutoff / af.getSampleRate()) * fftSize;
    int  lowCutoffBin =  (int) (lowCutoff / af.getSampleRate()) * fftSize;

    for (int i = highCutoffBin; i < fftSize; i++) {
        shiftedOut[i].r = 0;
        shiftedOut[i].i = 0;
    }

    for (int i = 0; i < lowCutoffBin; i++) {
        shiftedOut[i].r = 0;
        shiftedOut[i].i = 0;
    }

    // Apply filter
    kiss_fft(inv, shiftedOut, in);
    vector<double> output(fftSize);
    for (int i = 0; i < fftSize; i++) {
        output[i] = in[i].r / fftSize;
    }

    free(in);
    free(out);
    free(shiftedOut);
    kiss_fft_free(cfg);
    kiss_fft_free(inv);

    return output;
}

double Autotune::findShiftingFactor(double f) {
    if (f == 0) {
        return 0.0;
    }
    double C0 = 8.175;
    int octave = log2(f / C0);

    assert(octave <= 10);

    double closestNote = noteTbl[octave][0];
    double smallestDif = abs(noteTbl[octave][0] - f);
    
    for (int i = 1; i < noteTbl[octave].size(); i++) {
        double note = noteTbl[octave][i];
        double dif = abs(note - f);
        if (dif < smallestDif) {
            closestNote = note;
            smallestDif = dif;
        }
    }
    return pow(closestNote / f, this->intensity);
}

vector<double> Autotune::generateWindow(int size) {
    vector<double> window(size);
    for (int i = 0; i < size; i++) {
        window[i] = 0.5 * (1 - cos((2 * M_PI * i) / (size - 1)));
    }
    return window;

}

