#pragma once

#include "Mason/AudioManager.hpp"
#include "Mason/Component.hpp"

namespace Mason {
	class AudioManager;
	/** @enum SoundType
	* @brief enum holding possible sound types. Either EFFECT or MUSIC representing Mix_Chunk or Mix_Music in SDL_Mixer respectively
	*/
	enum SoundType {
		EFFECT, MUSIC
	};
	/** @class Audio
	* @brief Extends the Component class and holds information about a .wav sound file. 
	*/
	class Audio : public Component {
	public:
		/** @brief Initializes the Audio component. Calls the AudioManager to load its Audio Source.
		* @param file path to a .wav sound file. Must be a .wav file.
		* @param type either SoundType::EFFECT for Sound Effect or Soundtype::MUSIC for music. 
		* @param manager pointer to the active AudioManager
		* @param loops currently unused.
		*/
		void init(std::string file, SoundType type, AudioManager* manager, int loops = 0);

		/** @brief Plays the audio by querying the AudioManager.
		*/
		void play();
		SoundType type; ///< Holds the SoundType enum. Either SoundType::EFFECT or SoundType::Music
		std::string path; ///< Holds the path to the .wav audio file.		
	protected:
		/** @brief Constructor
		*/
		Audio(std::shared_ptr<GameObject> gameObject);
		friend class GameObject;
	private:
		int loops;
		AudioManager *manager; 
	};
}
