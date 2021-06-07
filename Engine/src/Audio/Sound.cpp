#include "Audio/Sound.hpp"

namespace BwatEngine::Audio
{


    AudioData::AudioData(std::string path)
    {
        AudioFile<float> audioFile(path);

        std::vector<uint8_t> data;
        audioFile.savePCMToBuffer(data);

        sampleRate = audioFile.getSampleRate();
        this->path = path;
        samples = std::move(data);

        if (audioFile.isStereo())
        {
            if (audioFile.getBitDepth() == 8)
                format = AL_FORMAT_STEREO8;
            else
                format = AL_FORMAT_STEREO16;
        }
        else
        {
            if (audioFile.getBitDepth() == 8)
                format = AL_FORMAT_MONO8;
            else
                format = AL_FORMAT_MONO16;
        }

        length = audioFile.getLengthInSeconds();
    }

    AudioData LoadWavFile(std::string path)
    {
        AudioData retData;

        AudioFile<float> audioFile(path);

        std::vector<uint8_t> data;
        audioFile.savePCMToBuffer(data);

        retData.sampleRate = audioFile.getSampleRate();
        retData.path = std::move(path);
        retData.samples = std::move(data);

        if (audioFile.isStereo())
        {
            if (audioFile.getBitDepth() == 8)
                retData.format = AL_FORMAT_STEREO8;
            else
                retData.format = AL_FORMAT_STEREO16;
        }
        else
        {
            if (audioFile.getBitDepth() == 8)
                retData.format = AL_FORMAT_MONO8;
            else
                retData.format = AL_FORMAT_MONO16;
        }

        retData.length = audioFile.getLengthInSeconds();

        return std::move(retData);
    }

    bool CheckALErrors()
    {
        ALenum error = alGetError();

        if (error != AL_NO_ERROR)
        {
            switch (error)
            {
                case AL_INVALID_NAME:
                    LogError("AL_INVALID_NAME: a bad name (ID) was passed to an OpenAL function");
                    break;
                case AL_INVALID_ENUM:
                    LogError("AL_INVALID_ENUM: an invalid enum value was passed to an OpenAL function");
                    break;
                case AL_INVALID_VALUE:
                    LogError("AL_INVALID_VALUE: an invalid value was passed to an OpenAL function");
                    break;
                case AL_INVALID_OPERATION:
                    LogError("AL_INVALID_OPERATION: the requested operation is not valid");
                    break;
                case AL_OUT_OF_MEMORY:
                    LogError("AL_OUT_OF_MEMORY: the requested operation resulted in OpenAL running out of memory");
                    break;
                default:
                    LogError("UNKNOWN AL ERROR: %s", error);
            }
            return false;
        }
        return true;
    }

    bool CheckALCErrors(ALCdevice *device)
    {
        ALCenum error = alcGetError(device);
        if (error != ALC_NO_ERROR)
        {
            switch (error)
            {
                case ALC_INVALID_VALUE:
                    LogError("ALC_INVALID_VALUE: an invalid value was passed to an OpenAL function");
                    break;
                case ALC_INVALID_DEVICE:
                    LogError("ALC_INVALID_DEVICE: a bad device was passed to an OpenAL function");
                    break;
                case ALC_INVALID_CONTEXT:
                    LogError("ALC_INVALID_CONTEXT: a bad context was passed to an OpenAL function");
                    break;
                case ALC_INVALID_ENUM:
                    LogError("ALC_INVALID_ENUM: an unknown enum value was passed to an OpenAL function");
                    break;
                case ALC_OUT_OF_MEMORY:
                    LogError("ALC_OUT_OF_MEMORY: an unknown enum value was passed to an OpenAL function");
                    break;
                default:
                    LogError("UNKNOWN ALC ERROR: %s", error);
            }
            return false;
        }
        return true;
    }

    bool InitOpenAL()
    {
        // Ouverture du device
        ALCdevice *device = alcOpenDevice(nullptr);
        if (!device)
        {
            CheckALCErrors(device);
            return false;
        }

        // Création du contexte
        ALCcontext *context = alcCreateContext(device, nullptr);
        if (!context)
        {
            CheckALCErrors(device);
            return false;
        }

        // Activation du contexte
        if (!alcMakeContextCurrent(context))
        {
            CheckALCErrors(device);
            return false;
        }

        LogInfo("[OpenAL] Context initialized");

        return true;
    }

    void ShutdownOpenAL()
    {
        LogInfo("[OpenAL] Shutting Down");

        ALCcontext *Context = alcGetCurrentContext();
        ALCdevice *Device = alcGetContextsDevice(Context);

        alcMakeContextCurrent(nullptr);
        alcDestroyContext(Context);

        alcCloseDevice(Device);
    }

    void GetDevices(std::vector<std::string> &devices)
    {
        // Clear potential garbage inside the list
        devices.clear();

        // Returns null-ended list of null-ended strings
        const ALCchar *DeviceList = alcGetString(nullptr, ALC_DEVICE_SPECIFIER);
        if (DeviceList)
        {
            while (strlen(DeviceList) > 0)
            {
                devices.emplace_back(DeviceList);
                DeviceList += strlen(DeviceList) + 1;
            }
        }
    }

    ALuint CreateSource(AudioData& audioData)
    {
        ALuint source;
        alGenSources(1, &source);
        CheckALErrors();
        return source;
    }

    void DestroySource(ALuint& source)
    {
        alDeleteSources(1, &source);
    }
}