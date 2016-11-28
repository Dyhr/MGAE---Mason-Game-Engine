#include "Mason/Audio.hpp"

#include <iostream>
#include <string>
#include <SDL_hints.h>
#include <SDL.h>

using namespace std;
using namespace Mason;

static Uint8 * audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play
static Uint8 * wav_buffer; // buffer containing our audio file

Audio::Audio(GameObject * gameObject) :Component(gameObject)
{
}

void Audio::init(string file, SoundType type, AudioManager * manager, int loops)
{
	this->manager = manager;
	path = file;
	this->type = type;
}

void Audio::playMePlease() {
	if (manager) {
		manager->AddAudioSource(this);
	}
}