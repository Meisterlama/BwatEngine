#include "Audio/Source.hpp"

namespace BwatEngine::Audio
{
    Source::Source()
    {
        alGenSources(1, &sourceID);
    }

    Source::Source(const AudioData& audioData)
    {
        alGenSources(1, &sourceID);
        SetAudioData(audioData);
    }

    Source::~Source()
    {
			// memory leak ?
//        alDeleteSources(1, &sourceID);
//        CheckALErrors();
    }

    void Source::SetPitch(float pitch)
    {
        alSourcef(sourceID, AL_PITCH, pitch);
    }

    void Source::SetGain(float gain)
    {
        alSourcef(sourceID, AL_GAIN, gain);
    }

    void Source::SetPosition(Math::Vec3f pos)
    {
        alSourcefv(sourceID, AL_POSITION, pos.values);
    }

    void Source::SetVelocity(Math::Vec3f vel)
    {
        alSourcefv(sourceID, AL_VELOCITY, vel.values);
    }

    void Source::SetLooping(bool loop)
    {
        alSourcei(sourceID, AL_LOOPING, (loop) ? AL_TRUE: AL_FALSE);
    }

    float Source::GetPitch()
    {
        float pitch;
        alGetSourcef(sourceID, AL_PITCH, &pitch);
        return pitch;
    }

    float Source::GetGain()
    {
        float gain;
        alGetSourcef(sourceID, AL_GAIN, &gain);
        return gain;
    }

    bool Source::GetLooping()
    {
        int loop;
        alGetSourcei(sourceID, AL_LOOPING, &loop);
        return (loop == AL_TRUE);
    }

    void Source::SetAudioData(const AudioData &audioData)
    {
        length = audioData.length;
        buffer.BufferAudioData(audioData);
        alSourcei(sourceID, AL_BUFFER, buffer.GetID());
    }

    void Source::Play()
    {
        alSourcePlay(sourceID);
    }

    void Source::Stop()
    {
        alSourceStop(sourceID);
    }
}
