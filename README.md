# Abstract
This project is an open-source C++ library enabling developers to transform audio effortlessly without DSP expertise. The current stage of development is building out the audio effects and tweaking them to be high quality. 

# Technologies used
* Uses Microsoft's [vcpkg](https://github.com/microsoft/vcpkg) as a package manager.
* Unit testing with Google Tests (gtests)
* CI/CD with Github worfklows for cross-platform builds

# Documentation
refer here for the documetnation
# How to use 
I am currently working on getting this package on the vcpkg open-source registry. It is taking longer than expected so for now this will have to do for now. 
#### Clone this repository
Currently you can use this library by importing is as a module in your project. In your project directory run the following: 
```Console
git clone https://github.com/EnzoMassyle/AudioFX.git
```
#### Setting up vcpkg
[follow this guide](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-bash) to set up vcpkg

#### Installing depenencies
Run this command to install the needed dependencies
```Console
vcpkg install fftw3 gtest libsndfile
```

#### Link with project

Add this code to your CMakeLists.txt
```Console

add_subdirectory(AudioFX)

target_include_directories(myproject PRIVATE AudioFX/include)

target_link_libraries(myproject PRIVATE fxaudio)

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
