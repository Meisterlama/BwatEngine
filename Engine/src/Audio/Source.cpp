#include "Audio/Source.hpp"

namespace BwatEngine::Audio
{
    Source::Source()
    {
        alGenSources(1, &sourceID);
    }

    Source::~Source()
    {
        if(alIsSource(sourceID))
            alDeleteSources(1, &sourceID);
        CheckALErrors();
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

    float Source::GetPitch() const
    {
        float pitch;
        alGetSourcef(sourceID, AL_PITCH, &pitch);
        return pitch;
    }

    float Source::GetGain() const
    {
        float gain;
        alGetSourcef(sourceID, AL_GAIN, &gain);
        return gain;
    }

    bool Source::GetLooping() const
    {
        int loop;
        alGetSourcei(sourceID, AL_LOOPING, &loop);
        return (loop == AL_TRUE);
    }

    void Source::Refresh()
    {
        if (audioData == nullptr)
            return;
        length = audioData->length;
        buffer.BufferAudioData(*audioData);
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