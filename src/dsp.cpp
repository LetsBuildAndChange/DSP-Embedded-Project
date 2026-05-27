#include <cmath>
#include "dsp.hpp"

void computeRMS(const void* inputBuffer, unsigned long frameCount, float &rms){
    float sqrSum = 0;
    const float* samples = static_cast<const float*>(inputBuffer);
    for(unsigned long i = 0; i < frameCount; ++i){
        sqrSum += samples[i] * samples[i];
    }
    rms = sqrt(sqrSum/frameCount); // compute RMS 
}
