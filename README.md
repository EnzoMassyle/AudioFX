# Abstract
This is a project that combines features of a music player and a Digital Audio Workstation (DAW). The end goal is for users to be able to upload songs, create playlists, and perform audio processing all in one app. Current stage of development is building out the audio effects and tweaking them to be high quality. 

# Key Features and Technologies used
This project is written in C++. Currently the basic flow of the program is processing a sound file and applying some audio processing technique to it. time stretching pitch shifting reverb and autotune have a working implementation.  

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
