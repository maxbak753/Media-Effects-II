#include <iostream>
#include <fftw3.h>        // For FFTW3 functions
#include <sndfile.h>      // For libsndfile functions

using namespace std;

int main() {
    cout << "Hello!" << endl;

    // Test FFTW3 - Create a simple FFT plan
    fftw_complex in[4], out[4];
    fftw_plan p = fftw_plan_dft_1d(4, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p); // Execute FFT

    // Test libsndfile - Open an audio file
    SNDFILE* file;
    SF_INFO sfinfo;
    file = sf_open("C:/Users/maxba/Documents/C++_Stuff/From_Matlab/Audio_Transform_Reconstructor/audio_files/Traditional Abballati - Roberto Alagna.wav", SFM_READ, &sfinfo);
    if (file) {
        cout << "Audio file opened successfully!" << endl;
        sf_close(file);
    } else {
        cout << "Failed to open audio file!" << endl;
    }

    return 0;
}
