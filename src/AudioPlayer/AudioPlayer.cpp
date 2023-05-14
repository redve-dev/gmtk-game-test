#include "AudioPlayer.hpp"
#include "../emscr.h"
#include <SDL2/SDL_mixer.h>
#include <algorithm>
#include <filesystem>

AudioPlayer::AudioPlayer(){
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024);
}

AudioPlayer::~AudioPlayer(){
	for(auto& el : music)
		Mix_FreeMusic(el);
	for(auto& el : effects)
		Mix_FreeChunk(el);
}

void AudioPlayer::SetVolume(double percente){
	// clamp between 0 and 100
	percente = std::max(std::min(100.0, percente), 0.0);
	volume = std::round(percente * 1.28 - 1);
	Mix_VolumeMusic(volume);
}

void AudioPlayer::PlayMusic(MUSIC m){
	Mix_PlayMusic(music.at(static_cast<int>(m)), -1);
}

void AudioPlayer::PlayEffect(EFFECT m){
	auto t = effects.at(static_cast<int>(m));
	Mix_VolumeChunk(t, 3*volume);
	Mix_PlayChannel(-1, t, 0);
}

void AudioPlayer::LoadEffects(const std::string & path){
#ifdef emscr
	auto files = std::__fs::filesystem::directory_iterator(path);
#else
	auto files = std::filesystem::directory_iterator(path);
#endif
	for(const auto& entry : files){
		const std::string t = entry.path();
		Mix_Chunk* m = Mix_LoadWAV(t.c_str());
		effects.push_back(m);
	}
}

void AudioPlayer::LoadMusic(const std::string & path){
#ifdef emscr
	auto files = std::__fs::filesystem::directory_iterator(path);
#else
	auto files = std::filesystem::directory_iterator(path);
#endif
	for(const auto& entry : files){
		const std::string t = entry.path();
		Mix_Music* m = Mix_LoadMUS(t.c_str());
		music.push_back(m);
	}
}
