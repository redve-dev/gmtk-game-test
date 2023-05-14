#include "Player.hpp"
#include "../func.hpp"
#include <SDL2/SDL_render.h>
#include <iterator>
#include <random>
#include <numeric>

Player::Player()
{
	ResetPosition();
	for(auto& el: next_tiles){
		el.RandomType(70, 60);
	}
}

Player::~Player(){


}

void Player::ResetPosition(){
	pos = glm::vec2(-2,4);
}

void Player::ResetPosition(std::vector<Tile>& arr){
	arr.at(TranslateCoordinates(-2,4)).type=Tile::Type::FLOOR;
	pos = glm::vec2(-2,4);
}
#include <iostream>
void Animate(Player& p, std::vector<Tile>& arr, SDL_Renderer* r){
	audio.PlayEffect(AudioPlayer::EFFECT::SZUR);
	//SDL_Delay(150);
	ClearRender(r);
	for(auto& el: arr){
		el.Draw(r);
	}
	p.Draw(r);
	SDL_RenderPresent(r);
}

void Player::Jump(int dir, int steps, std::vector<Tile>& arr, SDL_Renderer* ren){
	dir = std::min(dir, 5);
	steps = std::min(steps, 6);
	int block_counter=0;
	//pos += vecarr[dir]*(float)(steps);
	for(int s=steps; s>0; s--){
		if(block_counter>7){
			if(pos==glm::vec2( -2,4 )){
				ResetMap(arr, ren);
				return;
			}
			else{
				ResetPosition(arr);
				return;
			}
		}
		auto t = pos+vecarr[dir];
		if(TranslateCoordinates(t)<0){
			if(s==steps){
				s++;
				dir = (dir+1)%6;
				block_counter++;
				continue;
			}
			else{
				return;
			}
		}
		auto r = arr.at(TranslateCoordinates(t)).ActivateTile();
		if(r == 3){
			if(pos==glm::vec2(-2,4)){
				if(s==steps){
					s++;
					block_counter++;
					dir = (dir+1)%6;
					continue;
				}
			}
			pos = t;
			Animate(*this, arr, ren);
			ResetPosition(arr);
			return;
		}
		else if(r == 2) { 
			pos = t;
			Animate(*this, arr, ren);
			//SDL_Delay(500);
			ResetMap(arr, ren);
			ResetPosition();
			return; }
		else if(r == 1){
			if(s==steps){
				dir = (dir+1)%6;
				s++;
				block_counter++;
				continue;
			}
			else{
				break;
			}
		};
		//Animate(*this, arr, ren);
		pos = t;
		Animate(*this, arr, ren);
	}
}

#include <iostream>
void Player::Draw(SDL_Renderer* r){
	SDL_SetRenderDrawColor(r,255, 225, 0, 0);
	auto t=TransformSpace(pos);
	SDL_Rect rec{
		.x = static_cast<int>(t.x)-25,	
			.y = static_cast<int>(t.y)-30, 
			.w = 50,
			.h = 50
	};
	SDL_RenderCopy(r, txt, 0, &rec);
}

int PutTile(std::vector<Tile>& arr, Tile::Type t, int record){
	if(arr.at(record).type == t){
		return 1;
	}
	if(arr.at(record).type == Tile::Type::EXIT){
		return 1;
	}
	arr.at(record).ChangeType(t);
	return 0;
}

int GetTile(std::vector<Tile>& arr){
	auto mp = ( GetMouse() );
	auto dist=[](glm::vec2 p1, glm::vec2 p2){
		auto x=p1.x-p2.x;
		auto y=p1.y-p2.y;
		return x*x+y*y;
	};
	auto record = 0;
	for(int i=0; i<arr.size(); i++){
		auto t=TransformSpace(arr.at(i).pos);
		auto t1=TransformSpace(arr.at(record).pos);
		if(dist(mp, t)<dist(mp,t1)){
			record = i;
		}
	}
	return record;
}

#include <SDL2/SDL_image.h>
void Player::LoadTxt(SDL_Renderer* r){
	txt = IMG_LoadTexture(r,			"resources/txt/player.png");
	textures.at(0) = IMG_LoadTexture(r, "resources/txt/floor.png");
	textures.at(1) = IMG_LoadTexture(r, "resources/txt/hole.png");
	textures.at(2) = IMG_LoadTexture(r, "resources/txt/wall.png");
}

#include <algorithm>
int Player::Move(std::vector<Tile>& arr, SDL_Renderer* r, int record){
	auto t= PutTile(arr, next_tiles.at(0).type, record);
	//auto t=0;
	if(t!= 0) return 1;
	for(int i=0; i<3; i++){
		next_tiles[i]=next_tiles[i+1];
	}
	next_tiles.back().RandomType(70, 60);
	static std::array<int, 6> chances_dir={
		100,
		200,
		300,
		400,
		500,
		600
	};

	static std::array<int, 6> chances_dist={
		100,
		200,
		300,
		400,
		500,
		600
	};
	auto dir = RollADice(chances_dir);
	auto dist = RollADice(chances_dist);
	audio.PlayEffect(AudioPlayer::EFFECT::CUBE);
	//SDL_Delay(50);
	Jump(dir, dist, arr, r);
	return 0;
}

int RollADice(const std::array<int, 6>& chances){
	static std::random_device rd;  //Will be used to obtain a seed for the random number engine
	static std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	static std::discrete_distribution<int> distrib(chances.cbegin(), chances.cend());

	return distrib(gen);
}

void Player::ShowTiles(SDL_Renderer* r){
	auto draw=[](SDL_Renderer* r,int h, SDL_Texture* t){
		SDL_Rect rec{
			.x=750,
				.y=h*50+50,
				.w=30,
				.h=30
		};
		SDL_RenderCopy(r, t, 0, &rec);
	};
	//DrawRed(glm::vec2(765,65), r);
	for(int i=0; i<4; i++){
		int txt_num;
		if(next_tiles[i].type == Tile::Type::FLOOR){
			txt_num=0;
		}
		if(next_tiles[i].type == Tile::Type::HOLE){
			txt_num=1;
		}
		if(next_tiles[i].type == Tile::Type::WALL){
			txt_num=2;
		}
		draw(r, i, textures[txt_num]);
	}

}
