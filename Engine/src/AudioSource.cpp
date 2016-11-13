#include "AudioSource.hpp"

void AudioSource::playSound()
{
	ALsizei size = 1;
	ALuint *srcNames;
	alGenSources(size, srcNames);

	ALuint sourceID = srcNames[0];
	alSource3f(sourceID, AL_POSITION, position.x, position.y, position.z);
	alSourcef(sourceID, AL_GAIN, volume);

}
