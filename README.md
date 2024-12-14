# Abstract
This project attempts to implement a simplied version of the digial audio processing technology autotune. Autotune is a sound processing method which transforms sounds meant to correct a singer's voice that is slightly off-pitch to the nearest semitone. This technology is widely used in mainstream music production and this project here was to gain a basic understanding of how one might perform this and the steps that are taken. 

# Key Features and Technologies used
This project was completed in C++ and the main tool that was used to accomplish this technique was the fast fourier transform (FFT). The basic flow of the program is processing a sound file. Breaking up this file into smaller chunks and processing each chunk to find the most prominent frequency. After this point we calculate its nearest note on the given musical scale and perform a shift in the frequencies to match this. 

# How to Use
To use this application, put any voice samples in the samples folder. In src/main.cpp, we can specify what musical scale we want to follow when processing the file. Currently we can choose any of the major or minor scales. The default is C Major scale. 

navigate to the build directory \
`cd build`

excecute the Autotune excetuable providing a sound file. Here is provided with an example sound file \
`./Autotune Diner.wav`

A file titled out.wav will be written to the build directory
