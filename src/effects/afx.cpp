#include <../headers/afx.h>

vector<vector<double>> AFX::artificialReverb(vector<vector<double>> samples)
{
    int numChannels = samples.size();
    if (samples.empty() || samples[0].empty())
    {
        throw runtime_error("Invalid input: Empty sample buffer.");
    }

    int numSamples = samples[0].size();
    revmodel reverb;
    reverb.setdry(0.9);
    reverb.setwet(0.5);
    reverb.setroomsize(0.5);
    reverb.setwidth(0.1);
    reverb.setdamp(0.8);
    // Utils::gain(samples, 0.1);

    // Allocate buffers
    vector<double> inLeft(numSamples);
    vector<double> inRight(numSamples);
    vector<double> outLeft(numSamples);
    vector<double> outRight(numSamples);

    // Fill input buffers
    inLeft = samples[0];
    inRight = (numChannels > 1) ? samples[1] : inLeft;
    
    // Apply reverb
    reverb.processreplace(inLeft.data(), inRight.data(), outLeft.data(), outRight.data(), numSamples, 1);

    // Store processed output
    samples[0] = outLeft;
    if(numChannels > 1) {
        samples[1] = outRight;
    }

    MedianF filter = MedianF();
    filter.process(samples);
    Utils::normalize(samples);

    return samples;
}

vector<vector<double>> AFX::autotune(vector<vector<double>> samples, double intensity, string note, char scale, int sampleRate)
{
    Autotune autotune = Autotune(intensity, note, scale);
    autotune.fillNoteTable();
    return autotune.process(samples, sampleRate);
};

vector<vector<double>> AFX::reverse(vector<vector<double>> samples)
{
    for (int chan = 0; chan < samples.size(); chan++)
    {
        int l = 0;
        int r = samples[chan].size() - 1;
        while (l < r)
        {
            double temp = samples[chan][l];
            samples[chan][l] = samples[chan][r];
            samples[chan][r] = temp;
            l++;
            r--;
        }
    }

    return samples;
}

vector<vector<double>> AFX::demix(vector<vector<double>> samples, bool vocals)
{
    // // Set up Python configuration
    // PyStatus status;
    // PyConfig config;
    // PyConfig_InitPythonConfig(&config);

    // // Set the Python home directory to your virtual environment
    // const wchar_t* python_home = L"C:/Users/Enzo/Documents/funStuff/AudioFX/venv";
    // status = PyConfig_SetString(&config, &config.home, python_home);
    // if (PyStatus_Exception(status)) {
    //     PyConfig_Clear(&config);
    //     throw;
    // }
    
    // status = Py_InitializeFromConfig(&config);
    // PyConfig_Clear(&config);

    // if (PyStatus_Exception(status)) {
    //     std::cerr << "Failed to initialize Python with the correct home directory" << std::endl;
    //     throw;
    // }
    const char* command = "spleeter separate -p spleeter:5stems -o output ../samples/circles.mp3";
    int result = system(command);
    if (result == 0) {
    std::cout << "Command executed successfully" << std::endl;
    } else {
        std::cerr << "Command failed with exit code: " << result << std::endl;
    }
    // py::scoped_interpreter guard{};
    // py::exec(R"(
    //     import sys
    //     sys.path.append("C:/Users/Enzo/Documents/funStuff/AudioFX/src/effects")  # Adjust this path!
    //     sys.path.append("C:/Users/Enzo/Documents/funStuff/AudioFX/venv/Lib/site-packages")
    //     print("Python sys.path:", sys.path)  # Debugging
    //     print(sys.executable)
    // )");
    // py::module_ demix = py::module_::import("separate");
    // py::exec(R"(
    //     kwargs = dict(name="World", number=42)
    //     message = "Hello, {name}! The answer is {number}".format(**kwargs)
    //     print(message)
    // )");
    // int numChannels = samples.size();
    // for (int chan = 0; chan < numChannels; chan++)
    // {
    //     cout << chan << endl;
    //     // samples[chan] = demix.attr("demix")(samples,vocals).cast<vector<double>>();
    // }
    

    return samples;
}
