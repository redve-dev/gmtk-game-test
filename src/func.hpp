#pragma once
#include "glm/glm/vec2.hpp"
#include <SDL2/SDL.h>
#include <array>
#include <vector>
#include "Tile/Tile.hpp"
#include "AudioPlayer/AudioPlayer.hpp"

void DrawBall(glm::vec2 p, SDL_Renderer* r);
void DrawRed(const glm::vec2& pos, SDL_Renderer* r);
constexpr std::array<glm::vec2,6>vecarr={
	glm::vec2{1, 0},	// 0
	glm::vec2{0, 1},	// 1
	glm::vec2{-1, 1},	// 2
	glm::vec2{-1, 0},	// 3
	glm::vec2{0, -1},	// 4
	glm::vec2{1, -1}	// 5
};

int TranslateCoordinates(int x, int y);
int TranslateCoordinates(glm::vec2 p);
glm::vec2 TransformSpace(const glm::vec2&p);
glm::vec2 InvertTransformSpace(const glm::vec2& p);
void GenerateMap(std::vector<Tile>& arr);
glm::vec2 GetMouse();
int PutTile(std::vector<Tile>& arr, Tile::Type t, int);
void ResetMap(std::vector<Tile>&, SDL_Renderer*);
void ClearRender(SDL_Renderer*);
inline AudioPlayer audio;
int GetTile(std::vector<Tile>&);
