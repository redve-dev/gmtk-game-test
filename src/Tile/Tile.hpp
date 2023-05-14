#pragma once
#include "../glm/glm/vec2.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <vector>
#include <array>

class Player;
class Tile {
	public:
		enum class Type{
			FLOOR,
			HOLE,
			WALL,
			EXIT,
		};
	private:
		static std::array<SDL_Texture* ,5> txt;
		glm::vec2 pos;
		Type type;
	public:
		Tile(const glm::vec2&);
		Tile()=default;
		~Tile();
		void ChangeType(Type);
		void RandomType(int, int);
		int ActivateTile() const;
		static void LoadTexture(SDL_Renderer*);
		void Draw(SDL_Renderer*);
		void MakeExit();
		friend int GetTile(std::vector<Tile>&);
		//friend void PutTile(std::vector<Tile>&, Type);
		friend int main();
		friend class Player;
		friend int PutTile(std::vector<Tile>&, Type, int);
		void Highlight(SDL_Renderer*);
};
