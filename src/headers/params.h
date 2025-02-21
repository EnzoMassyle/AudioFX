#ifndef PARAMS_H
#define PARAMS_H

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

#define FRAME_SZ 4096
#define HOP_SZ 1024
#endif