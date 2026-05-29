#include <iostream>
#include <cmath>
#include <portaudio.h>
#include <cstring>
#include <chrono>
#include <atomic>
#include <fftw3.h>
#include <mutex>

#include "dsp.hpp"

#define SAMPLE_RATE 48000
#define FRAMES_PER_BUFFER 1024 // the size of the buffer that we get in our callback function
// captures the amplitude of our wave form at a given moment
// does this 48000 times per second
// after I get 1024 samples takes take this and pass it to the callback


using namespace std;

// std::mutex mtx;
// float* latestAudioBlock[1024];
// bool isBlockAvailable = false;


// 1. Make sure CMake links FFTW.
// 2. Include fftw3.h and confirm the project still builds.
// 3. Create constants: sample rate, FFT size, test frequency.
// 4. Allocate FFTW input array.
// 5. Allocate FFTW output array.
// 6. Create FFTW plan.
// 7. Fill input with synthetic 440 Hz sine wave.
// 8. Execute FFT.
// 9. Loop through output bins and compute magnitudes.
// 10. Find the max bin.
// 11. Convert max bin to frequency.
// 12. Print the result.
// 13. Destroy/free FFTW resources.
atomic<double> latestRms = 0;
atomic<double> latestProcessingTime = 0;
atomic<double> latestDominantFrequency = 0;


// FFTW configuration that domputes the Dominant Frequency for each Block 
double computeDominantFrequency(const float* samples, int frameCount){
    int FFT_size = frameCount;
    int outputSize = FFT_size/2 + 1;
    // int N = FFT_size/2 + 1;
    double in[1024];
    fftw_complex out[513];
    // allocate input buffer
    fftw_plan p;
    // n = size of transform, FFTW_forward = direction, FFTW_Estimate = flag argument
    p =  fftw_plan_dft_r2c_1d(FFT_size, in, out, FFTW_ESTIMATE);
    // Filling input with synthetic 440 Hz sine wave 
    for(int i = 0; i < FFT_size; i++){
          in[i] = static_cast<double>(samples[i]);
    }
    fftw_execute(p); // transform itself is executed 
    // output
    double maxMag = 0;
    double maxBin = 0;
     double dominantFrequency = 0;
    for(int bin = 1; bin < outputSize; bin++){
        double mag = sqrt(out[bin][0] * out[bin][0] + out[bin][1] * out[bin][1]);
        if(mag > maxMag){
            maxMag = mag;
            maxBin = bin;
        }
        // double currentFrequency = bin * SAMPLE_RATE / FFT_size;

            //  std::cout << "FFT size: " << FFT_size << std::endl;
            // std::cout << "Sample rate: " << SAMPLE_RATE << " Hz" << std::endl;
            // std::cout << "Bin spacing: " << static_cast<double>(SAMPLE_RATE) / FFT_size << " Hz" << std::endl;
            // std::cout << "Expected tone: 440Hz" << std::endl;
            //  std::cout << "Current bin: " << bin << std::endl;
            //  std::cout << "Current bin Magnitude: " << mag << std::endl;
            // std::cout << "Current bin Frequency: " << currentFrequency << std::endl;
            // std::cout << "Dominant bin: " << maxBin << std::endl;
            // std::cout << "Dominant frequency: " << dominantFrequency << " Hz" << std::endl;
    }

    dominantFrequency = maxBin * SAMPLE_RATE / FFT_size;
    
    fftw_destroy_plan(p); 
    return dominantFrequency;
}

const double blockDuration = 1000.0 * FRAMES_PER_BUFFER / SAMPLE_RATE;
// AUDIO CALLBACK FUnction Start 
static int audioCallback(const void* inputBuffer,
                         void* outputBuffer,
                         unsigned long frameCount,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void* userData){
    
    (void)outputBuffer;
    (void)timeInfo;
    (void)statusFlags;
    (void)userData;
    if(inputBuffer == NULL){
        return -1;
    }   


    auto start = chrono::steady_clock::now(); // start processing time
    // Convert input buffer to float array then Compute RMS
    const float* samples = static_cast<const float*>(inputBuffer);
    float rms = 0;
    computeRMS(samples, frameCount, rms);
    double dominantFrequency = computeDominantFrequency(samples, frameCount);

    auto end = chrono::steady_clock::now();// end processing time 

    chrono::duration<double, milli> elapsed = end - start;
    double processingTime = elapsed.count();
    latestDominantFrequency = dominantFrequency; 
    latestRms = rms;
    latestProcessingTime = processingTime;
    return paContinue;
}
// CALL BACK Function end
void checkError(PaError err){
    if(err != paNoError){
        cout << "PortAudio Error"<< Pa_GetErrorText(err);
        exit(EXIT_FAILURE);
    }
}
int main() {
    cout << "Raspberry Pi DSP project started." << endl;

    // runSyntheticFftTest();
    
    PaError err = Pa_Initialize();
    // paTestDatadata;
    checkError(err);

    // int numDevices = Pa_GetDeviceCount(); // number of devices portAudio has available for us
    // cout << "Number of Devices" << numDevices << endl;
    // if(numDevices < 0){
    //     cout << "Error getting the device count" << endl;
    //    exit(EXIT_FAILURE);
    // }
    // else if(numDevices == 0){
    //    cout << "No available audio devices on this machine" << endl;
    //    exit(EXIT_SUCCESS);
    // }

    // const PaDeviceInfo* deviceInfo; // track device info for each device

    // for(int i = 0; i < numDevices; i++){
    //     deviceInfo = Pa_GetDeviceInfo(i);
    //     cout << "Device" << i << endl;
    //     cout << "name: "<< deviceInfo->name << endl;
    //     cout << "maxInputChannels: "<< deviceInfo->maxInputChannels << endl;
    //     cout << "maxOutputChannels: "<< deviceInfo->maxOutputChannels << endl;
    //     cout << "defaultSampleRate: "<< deviceInfo->defaultSampleRate << endl;

    // }

    int device = 1;
    // parameters of the stream
    PaStreamParameters inputParameters;
    // PaStreamParameters outputParameters;

    memset(&inputParameters, 0, sizeof(inputParameters));
    inputParameters.device = device; 
    inputParameters.channelCount = 1;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    // memset(&outputParameters, 0, sizeof(outputParameters));
    // outputParameters.device = device; 
    // outputParameters.channelCount = 2;
    // outputParameters.sampleFormat = paFloat32;
    // outputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency; // runs this in real time 
    // outputParameters.hostApiSpecificStreamInfo = NULL;
        //stream that captures the audio 

    PaStream* stream;
    err = Pa_OpenStream(
        &stream, 
        &inputParameters, 
        NULL, 
        SAMPLE_RATE, 
        FRAMES_PER_BUFFER,
        paNoFlag,
        audioCallback,
        NULL
    );
    checkError(err);

    err = Pa_StartStream(stream);
    checkError(err);
    cout << "Stream opened successfully." << endl;

    // ASK AI: WHY AM I DOING THIS?
   
    auto programStart = chrono::steady_clock::now();
    
    while(chrono::steady_clock::now() - programStart < chrono::seconds(30)){
       cout << "RMS: " << latestRms
          << " | processing: " << latestProcessingTime << " ms" 
          << "| latestDominantFrequency:" << latestDominantFrequency << " Hz" 
          << " | budget: " << blockDuration << " ms"
          << endl;
          Pa_Sleep(500);
    }

    err = Pa_StopStream(stream);
    checkError(err);

    err = Pa_CloseStream(stream);
    checkError(err);

    err = Pa_Terminate();
    checkError(err);

   

    return 0;
}