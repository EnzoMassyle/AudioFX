#ifndef PARAMS_H
#define PARAMS_H

#define CHUNK_SIZE 80000
#define TIME_CHUNK_SZ 10000
#define TIME_OFFSET 400
#define NUM_OVERLAP 2.5

/* Pitch Shifting */
#define PITCH_CHUNK_SZ 5000
#define PITCH_OFFSET 200
#define PITCH_OVERLAP 6


/* Autotune */
#define AT_CHUNK_SZ 5000
#define AT_OFFSET 100
#define AT_OVERLAP 4

/* Reverb */
#define REVERB_CHUNK_SZ 25000
#define REVERB_CHUNK_OFFSET 500
#define REVERB_OVERLAP 4

/* File reading buffer */
#define BUFFER_LEN 512
#endif