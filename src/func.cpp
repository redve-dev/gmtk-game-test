#include "func.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <cmath>

void DrawBall(glm::vec2 p, SDL_Renderer* r){
	int radius=24;
	for(double a=0.0f; a<2*3.14159265f; a+=0.01){
		SDL_RenderDrawLine(r, p.x, p.y, cos(a)*radius+p.x, sin(a)*radius+p.y);
	}
}

int TranslateCoordinates(glm::vec2 p){
	return TranslateCoordinates(p.x, p.y);
}

int TranslateCoordinates(int x, int y){
	int result=0;
	if(std::abs(x)>6)
		return -1;
	if(x<=0){
		result -= 13*x;
		if(y< (-6) || y> 6)
			return -1;
		if(y<=0){
			result -= 14*y;
			if((-x-y)>6) return -1;
		}
		if(y>0){
			result += y+6;
			if(y>6) return -1;
		}
	}
	if(x>0){
		auto k=(7-x);
		result += 127-(k*k);
		if(y>0){
			result += (y+k-1);
			if((x+y)>6) return -1;
		}
		if(y<0){
			if(y<(-6)) return -1;
			if(std::abs(y)< (x)){
				auto f=[](int x){auto k=(7-x); return 127-(k*k);};
				result = f(x+y) -y;
			}
			else{
				result = x + 14*(-x-y);
			}
		}

	}
	return result;
}

glm::vec2 TransformSpace(const glm::vec2& p){
	auto origin = glm::vec2(400,300);
	auto x = p.x + p.y/2.0;
	auto y =(sqrt(3)/2.0)*p.y;
	float c=50;
	auto newVec=glm::vec2(x*c,c*y);
	return newVec+origin;
}

glm::vec2 InvertTransformSpace(const glm::vec2& p){
	auto origin = glm::vec2(400, 300);
	float c=50;
	glm::vec2 newVec = p-origin;
	float x= newVec.x * (1.0/c);
	float y= newVec.y * (1.0/c);
	auto py = y*static_cast<float>(2.0/sqrt(3));
	auto px = x-(py / 2.0);

	return glm::vec2(px, py);

}

void DrawRed(const glm::vec2& pos, SDL_Renderer* r){
	SDL_SetRenderDrawColor(r,255,0,0,0);
	DrawBall(pos, r);
}

glm::vec2 GetMouse(){
	int x, y;
	SDL_GetMouseState(&x, &y);
	return glm::vec2(x,y);
}

void GenerateMap(std::vector<Tile>& arr){
	for(int i=6; i>=0; i--){
		auto b = float(6-i)*vecarr.at(3);
		arr.push_back(Tile(b));
		for(int j=1; j<7; j++){
			auto t=float(j)*vecarr.at(5);
			arr.push_back(Tile(t+b));
		}
		for(int j=1; j<7; j++){
			auto t=float(j)*vecarr.at(1);
			arr.push_back(Tile(t+b));
		}
	}
	for(int i=6; i>0; i--){
		auto b=float(7-i)*vecarr.at(0);
		arr.push_back(Tile(b));
		for(int j=1; j<=i-1; j++){
			auto t=float(j)*vecarr.at(5);
			arr.push_back(Tile(t+b));
		}
		for(int j=1; j<=i-1; j++){
			auto t=float(j)*vecarr.at(1);
			arr.push_back(Tile(t+b));
		}
	}
	for(auto &t : arr){
		t.RandomType(85, 65);
	}
	for(int x=0; x<=6; x++)
		arr.at(TranslateCoordinates(x, -6)).MakeExit();
	arr.at(TranslateCoordinates(-2,4)).ChangeType(Tile::Type::FLOOR);
}

void ClearRender(SDL_Renderer* r){
	static SDL_Texture* t=IMG_LoadTexture(r, "resources/txt/background2.png");
	SDL_Rect rec;
	rec.x=0; rec.y=0; rec.w=800; rec.h=600;
	SDL_RenderCopy(r, t, 0, &rec);
}

void ResetMap(std::vector<Tile>& arr, SDL_Renderer* r){
	//SDL_SetRenderDrawColor(r, 120, 120, 120, 0);
	//SDL_RenderClear(r);
	ClearRender(r);

arr.clear();
	GenerateMap(arr);
	audio.LoadMusic("resources/music/");
	audio.LoadEffects("resources/effects/");
	audio.PlayMusic(AudioPlayer::MUSIC::DEFAULT);
	audio.SetVolume(10);
}

