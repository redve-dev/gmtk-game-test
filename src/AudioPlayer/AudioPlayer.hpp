#include <SDL2/SDL_mixer.h>
#include <vector>
#include <string>

class AudioPlayer {
	private:
		int volume;
		std::vector<Mix_Music*> music;
		std::vector<Mix_Chunk*> effects;

	public:
		AudioPlayer();
		~AudioPlayer();
		void SetVolume(double);
		enum class MUSIC{
			DEFAULT,
		};

		enum class EFFECT{
			CUBE,
			MOZE,
			SZUR,
			DEFAULT,
		};
		void PlayMusic(MUSIC);
		void PlayEffect(EFFECT);
		void LoadEffects(const std::string&);
		void LoadMusic(const std::string&);
};
