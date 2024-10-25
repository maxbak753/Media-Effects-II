// WAV File Format Info:
// http://soundfile.sapp.org/doc/WaveFormat/
// Video Tutorial: 
// https://youtu.be/rHqkeLxAsTc?si=vITjSY89kgSKAOfN

#include <iostream>
#include <fstream>
#include <cmath> // sin()

using namespace std;

// RIFF Sub-Chunk
const string chunk_id = "RIFF"; // 4 bytes
const string chunk_size = "----"; // 4 bytes
const string format = "WAVE"; // 4 bytes

// FMT Sub-Chunk
const string subchunk1_id = "fmt "; // 4 bytes (need the space)
const int subchunk1_size = 16; // 4 bytes
const int audio_format = 1; // 2 bytes
const int num_channels = 2; // 2 bytes
const int sample_rate = 44100; // 4 bytes
const int bits_per_sample = 16; // 2 bytes (later in header, but needed to calculate next 2 values)
const int byte_rate = sample_rate * num_channels * (bits_per_sample / 8); // 4 bytes
const int block_align = num_channels * (bits_per_sample / 8); // 2 bytes
// bits_per_sample should be here in the header

// Data Sub-Chunk
const string subchunk2_id = "data"; // 4 bytes
const string subchunk2_size = "----"; // 4 bytes

const int duration = 2; // audio file duration in seconds
const int max_amplitude = 32760; // the bits_per_sample is 16 bits, so 2^16 possible numbers, but that includes +-, and our audio is centered at 0 in amplitude, so divided by 2: (2^16)/2 = 32767
const double frequency = 250; // frequency of sinusoidal wave


void write_as_bytes(ofstream &file, int value, int byte_size) {
    // use ofstream class function "write()" to write things in binary and specify byte size
    // 1. take value and cast it as a constant character pointer
    //    (this makes it the correct input type for the write() function)
    // 2. pass the desired byte size as the 2nd input
    file.write(reinterpret_cast<const char*>(&value), byte_size);
}

int main() {
    ofstream wav; // audio file
    wav.open("test.wav", ios::binary); // open file & put in binary mode

    if (wav.is_open()) {
        cout << "Opened File" << endl;
        // HEADER ~_~_~_~_~_~_~_~_~_~_~_~_~_~_
        // Write header info to file without any spaces or newlines...
        // RIFF Sub-Chunk
        wav << chunk_id;
        wav << chunk_size;
        wav << format;
        // FMT Sub-Chunk
        wav << subchunk1_id;
        write_as_bytes(wav, subchunk1_size, 4); // even though int=4 bytes it may be different on other machines, so we specify it here
        write_as_bytes(wav, audio_format, 2);
        write_as_bytes(wav, num_channels, 2);
        write_as_bytes(wav, sample_rate, 4);
        write_as_bytes(wav, byte_rate, 4);
        write_as_bytes(wav, block_align, 2);
        write_as_bytes(wav, bits_per_sample, 2);
        // Data Sub-Chunk
        wav << subchunk2_id;
        wav << subchunk2_size;

        cout << "Wrote Header" << endl;

        int start_audio = wav.tellp(); // notes where we are in the file at this point (before audio data)

        // DATA CREATION ~_~_~_~_~_~_~_~_~_~_~_~_~_~_
        for (int i = 0; i < (sample_rate * duration); i++) {
            // linearly increasing amplitude from minimum to maximum
            double amplitude = ((double)i / (sample_rate * duration)) * max_amplitude;
            // sinewave
            double value = sin((2 * 3.14 * i * frequency) / sample_rate);
            // channel values
            double channel1 = amplitude * value; // increasing amplitude
            double channel2 = (max_amplitude - amplitude) * value; // decreasing amplitude
            // write to file
            write_as_bytes(wav, channel1, 2);
            write_as_bytes(wav, channel2, 2);
        }

        cout << "Wrote Data" << endl;

        int end_audio = wav.tellp(); // notes where the end of the audio data is
        
        wav.seekp(start_audio - 4); // go back 4 bytes to the subchunk2_size position
        write_as_bytes(wav, end_audio - start_audio, 4); // enter the length of the audio data (subchunk2_size)

        wav.seekp(4, ios::beg); // go to 4 bytes after the beginning of the file to where chunk_size is located
        write_as_bytes(wav, 36 + (end_audio - start_audio), 4); // 36 + subchunk2_size, but this is equivalent
    } else {
        cout << "Didn't open!" << endl;
    }
    cout << "Closing File... ";
    wav.close(); // close file
    cout << "Done." << endl;
    return 0;
}