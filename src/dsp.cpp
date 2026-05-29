#include <cmath>
#include "dsp.hpp"

void computeRMS(const float* samples, unsigned long frameCount, float &rms){
    float sqrSum = 0;
    for(unsigned long i = 0; i < frameCount; ++i){
        sqrSum += samples[i] * samples[i];
    }
    rms = sqrt(sqrSum/frameCount); // compute RMS 
}
