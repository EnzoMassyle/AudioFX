#include <vector>
#include "filehandler.h"
#include "utils.h"
#include "convreverb.h"
#include "timestretch.h"
#include "autotune.h"
#include "tempo.h"
#include "eq.h"



using namespace std;

/**
 * @class AFX
 * @brief Main class to access library functions
 * 
 * The AFX class provides audio effects such as autotune, time stretching, 
 * convolution reverb, pitch shifting, and equalization.
 */
class AFX
{
public:
    /**
     * @brief Pitch correct vocals to the nearest correct note on musical scale (either major 'M' or minor 'm'). This one isn't very high quality I have been struggling with this one ;/
     * 
     * @param samples -> audio samples separated by channel
     * @param sr -> sample rate
     * @param intensity -> Determines how strong to apply the autotune effect
     * @param note -> The musical note to use as the root note
     * @param scale -> Category of semitones (major or minor)
     * 
     * @returns Tuned audio samples
     */
    vector<vector<double>> autotune(const vector<vector<double>>& samples, double intensity, string note, char scale, int sr);
    /**
     * @brief Use phase vocoder to time stretch/compress audio samples
     * 
     * @param samples -> audio samples separated by channel
     * @param stretchFactor ->  > 1 will stretch the audio. < 1 will compress the audio
     * 
     * @returns Stretched/Compressed audio samples
     */
    vector<vector<double>> timeStretch(const vector<vector<double>>& samples, double stretchFactor) { return TimeStretch::changeSpeed(samples, stretchFactor); };
    /**
     * @brief Perform sinc interpolation to resample audio samples at a different playback rate
     * 
     * @param samples -> audio samples separated by channel
     * @param r -> resampling rate
     * 
     * @returns Modified audio samples
     */
    vector<vector<double>> changeTempo(const vector<vector<double>>& samples, double r) {return Tempo::changeTempo(samples, r);};
    /**
     * @brief Apply convolution based reverb to audio samples based on an impulse response. They can be found in assets/ir
     * 
     * @param samples -> audio samples separated by channel
     * @param room -> room name of impulse response
     * 
     * @returns Modified audio samples
     */
    vector<vector<double>> convReverb(vector<vector<double>>& samples, const vector<vector<double>>& irSamples) {return Reverb::convReverb(samples, irSamples);};
    /**
     * @brief Reverse audio samples resulting in audio played backwards
     * 
     * @param samples -> audio samples separated by channel
     * 
     * @returns Modified audio samples
     */
    vector<vector<double>> reverse(vector<vector<double>>& samples);
    /**
     * @brief Shift pitch using a phase vocoder
     * 
     * @param samples -> audio samples separated by channel
     * @param semitones -> number of semitones to shift by
     * 
     * @returns Modified audio samples
     */
    vector<vector<double>> pitchShift(vector<vector<double>>& samples, double semitones);

    /**
     * @brief take input samples, shift the pitch and scale amplitudes. Layer on top of existing audio
     * @param samples -> audio samples separated by channel
     * @param semitones -> number of semitones to shift by
     * @param g -> gain to apply to layered audio
     * 
     * @returns Modified audio samples
     */
    vector<vector<double>> layer(vector<vector<double>> samples, double semitones, double g);

    /**
     * @brief create a parametric equalizer with 8 Biquad filters
     * 
     * @param sampleRate -> sample rate of audio samples default is 44.1kHz
     * 
     * @returns EQ object instance 
     */
    EQ createEQ(int sampleRate = 44100) {return EQ(sampleRate);}
};