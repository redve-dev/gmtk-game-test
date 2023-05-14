#include "../func.hpp"
#include "Tile.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <random>

Tile::Tile(const glm::vec2& p):
	pos(p),
	type(Type::FLOOR)
{


}

Tile::~Tile(){


}

void Tile::ChangeType(Type t){
	type = t;
	if(t==Type::HOLE){
		audio.PlayEffect(AudioPlayer::EFFECT::MOZE);
	}
}

void Tile::RandomType(int w, int h){
	static auto distributor = std::uniform_int_distribution<int>(0, 100);
	static std::random_device rd;
	static auto engine = std::mt19937(rd());
	auto num = distributor(engine);
	if(num >w) type = Type::WALL;
	else if(num >h) type = Type::HOLE;
	else type = Type::FLOOR;
	//std::cout<<"chaning type to: "<<static_cast<int>( type )<<std::endl;
}

int Tile::ActivateTile()const {
	if (type==Type::FLOOR) return 0;
	if (type==Type::HOLE) return 3;
	if (type==Type::WALL) return 1;
	if (type==Type::EXIT) return 2;
	return -5;
}

std::array<SDL_Texture*, 5> Tile::txt;
void Tile::LoadTexture(SDL_Renderer* r){
	txt.at(0) = IMG_LoadTexture(r, "resources/txt/floor.png");
	txt.at(1) = IMG_LoadTexture(r, "resources/txt/hole.png");
	txt.at(2) = IMG_LoadTexture(r, "resources/txt/wall.png");
	txt.at(3) = IMG_LoadTexture(r, "resources/txt/gate.png");
	txt.at(4) = IMG_LoadTexture(r, "resources/txt/highlight.png");

}


#include <iostream>

void Tile::Draw(SDL_Renderer* r){
	auto newVec = TransformSpace(pos);
		int size=50;
		SDL_Rect rec{
			.x=static_cast<int>(newVec.x - size/2.0),
				.y=static_cast<int>(newVec.y - size/2.0),
				.w=size,
				.h=static_cast<int>(size*1.1)
		};
		SDL_RenderCopy(r, txt.at(static_cast<int>( type )), 0, &rec);
}


void Tile::MakeExit(){
	type = Type::EXIT;
}

void Tile::Highlight(SDL_Renderer* r){

	auto newVec = TransformSpace(pos);
		int size=50;
		SDL_Rect rec{
			.x=static_cast<int>(newVec.x - size/2.0),
				.y=static_cast<int>(newVec.y - size/2.0),
				.w=size,
				.h=static_cast<int>(size*1.1)
		};
		SDL_RenderCopy(r, txt.at(4), 0, &rec);
}
