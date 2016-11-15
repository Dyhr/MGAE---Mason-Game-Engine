#include "Audio.hpp"
#include <iostream>
#include <string>

using namespace std;


static Uint8 * audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play
static Uint8 * wav_buffer; // buffer containing our audio file

void audio_callback(void * userdata, Uint8 * stream, int len);


Audio::Audio(GameObject * gameObject) :Component(gameObject)
{
}

void Audio::init(std::string file)
{
	path = file.c_str();
}


void Audio::play()
{
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		return;

	// local variables
	static Uint32 wav_length; // length of our sample
	static Uint8 *wav_buffer; // buffer containing our audio file
	static SDL_AudioSpec wav_spec; // the specs of our piece of music


	/* Load the WAV */
	// the specs, length and buffer of our wav are filled
	if (SDL_LoadWAV(path.c_str(), &wav_spec, &wav_buffer, &wav_length) == NULL) {
		return;
	}
	// set the callback function
	wav_spec.callback = audio_callback;
	wav_spec.userdata = NULL;
	// set our global static variables
	audio_pos = wav_buffer; // copy sound buffer
	audio_len = wav_length; // copy file length

							/* Open the audio device */
	if (SDL_OpenAudio(&wav_spec, NULL) < 0) {
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		return;
	}

	/* Start playing */
	SDL_PauseAudio(0);


}

void audio_callback(void *userdata, Uint8 *stream, int len) {

	if (audio_len == 0)
		return;

	len = (len > audio_len ? audio_len : len);
	SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
	//SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

	audio_pos += len;
	audio_len -= len;
}

void Audio::cleanUp()
{	
	if (isPlaying()) {
		// wait until we're not playing	
	}
	else {
		// shut everything down
		SDL_CloseAudio();
		SDL_FreeWAV(wav_buffer);
	}
}

bool Audio::isPlaying()
{
	if (audio_len > 0) {
		return true;
	}
	else {
		return false;
	}
}



