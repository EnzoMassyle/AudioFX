# Abstract
This project is an open-source C++ library enabling developers to transform audio effortlessly without DSP expertise. I mainly did this project to get a better understanding of digital signal processing and I have always been a sound nerd. This library provides methods for offline audio processing. Methods have been optimized for speed and quality.

# Technologies used
* Uses Microsoft's [vcpkg](https://github.com/microsoft/vcpkg) as a package manager.
* Unit testing with Google Tests (gtests)
* CI/CD with Github worfklows for cross-platform builds

# Documentation
Access library documentation [here](https://enzomassyle.github.io/AudioFX/index.html)

# Setting up vcpkg
[follow this guide](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-bash) to set up vcpkg for your build system
# How to use 
This library is a port on vcpkg. Using this library just requires adding the port.

If you are running vcpkg in classic mode run this command
```Console
vcpkg install fxaudio
```

If you are running vcpkg in manifest mode run this command
```Console
vcpkg add port fxaudio
```

#### Link with project with CMake

If you are using CMake as your build system add this code to your CMakeLists.txt
```Console
find_package(FXAUDIO CONFIG REQUIRED)
target_link_libraries(myproject PRIVATE FXAUDIO::fxaudio)
```
# Example Code
This is a small example of how to use some the classes and methods provided. 
```Console
#include<fxaudio.h>

int main() {
    FileHandler fh = FileHandler();
    AudioFile af = fh.open("../mysndfile.wav");
    AFX afx = AFX();
    af.samples = afx.pitchShift(af.samples, 5);
    fh.write(af);
}
```







<!-- # How to Use
To use this application, put any voice samples in the samples folder. In src/main.cpp, apply audio processing to a given .mp3 or .wav file

First install [libsndfile](https://github.com/libsndfile/libsndfile)
Clone this [FFT Repo](https://github.com/mborgerding/kissfft)

navigate to the build directory 

run `cd build` \
run `cmake ..` \
run `make` 

excecute the `mc` excetuable providing a sound file. Here is provided with an example sound file \
`./mc Diner.wav`

A file titled out.wav will be written to the build directory -->
