#pragma once
#include "../func.hpp"
#include <SDL2/SDL_render.h>
#include <vector>
#include "../glm/glm/vec2.hpp"
#include "../Tile/Tile.hpp"

class Tile;
class Player {
	private:
		glm::vec2 pos;
		std::array<Tile, 4> next_tiles;
		std::array<SDL_Texture*, 4> textures;
		SDL_Texture* txt;

	public:
		Player();
		~Player();
		void ResetPosition();
		void ResetPosition(std::vector<Tile>& arr);
		void Jump(int dir, int length, std::vector<Tile>&, SDL_Renderer*);
		void Draw(SDL_Renderer* r);
		void LoadTxt(SDL_Renderer* r);
		//void Drop(std::vector<Tile>&);
		int Move(std::vector<Tile>&, SDL_Renderer*, int);
		int RollDirection();
		int RollDistance();
		void ShowTiles(SDL_Renderer*);
		friend void Animate(SDL_Renderer*, const glm::vec2&, Player&);
};

int RollADice(const std::array<int,6>&);
