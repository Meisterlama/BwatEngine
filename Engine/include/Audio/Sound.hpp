#ifndef ENGINE_AUDIO_SOUND_HPP
#define ENGINE_AUDIO_SOUND_HPP

#include "Debug/Logger.hpp"

#include "AL/al.h"
#include "AL/alc.h"

#include <vector>
#include <string>

#include "AudioFile.h"

namespace BwatEngine::Audio
{
    struct AudioData
    {
        std::string path;
        std::vector<uint8_t> samples;
        ALuint sampleRate;
        ALenum format;
        float length;

        AudioData() = default;
        AudioData(std::string path);
    };


    AudioData LoadWavFile(std::string path);

    bool CheckALErrors();

    bool CheckALCErrors(ALCdevice *device);

    bool InitOpenAL();

    void ShutdownOpenAL();

    void GetDevices(std::vector<std::string> &devices);

    ALuint CreateSource(AudioData& audioData);
    void DestroySource(ALuint& source);

    void SetPitch();
    void SetGain();

    ALuint CreateBuffer();
    void BufferData();
    void DestroyBuffer(ALuint& buffer);
}

#endif //ENGINE_AUDIO_SOUND_HPP
