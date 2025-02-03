#include <freeverb/Components/revmodel.hpp>
#include <filters/lp.h>
#include <filehandler.h>
#include <utils.h>
#include <convreverb.h>
#include <pitchshift.h>
#include <timestretch.h>
#include <autotune.h>
#include <vector>


using namespace std;
class AFX
{
public:
    vector<vector<double>> artificialReverb(vector<vector<double>> samples);
    vector<vector<double>> convReverb(vector<vector<double>> samples, string room = "CHURCH") { return Reverb::convReverb(samples, room); };
    vector<vector<double>> pitchShift(vector<vector<double>> samples, double pitchFactor) { return PitchShift::changePitch(samples, pitchFactor); };
    vector<vector<double>> timeStretch(vector<vector<double>> samples, double stretchFactor) { return TimeStretch::changeSpeed(samples, stretchFactor); };
    vector<vector<double>> reverse(vector<vector<double>> samples);
    vector<vector<double>> autotune(vector<vector<double>> samples, double intensity, string note, char scale, int sampleRate);
};