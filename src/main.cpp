/*
   DISCALIMER
   I know that global variables, main loop function, and this file in general is terrible.
   that's because it was meant to be used with emscripten.
   Also, the code will not be maintained, and i had 4 hours to get it to work.
   That's why i decided to just make it working, instead focusing on a nice code style
   */

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <vector>
#include <SDL2/SDL.h>
#include "Tile/Tile.hpp"
#include "Player/Player.hpp"
#include "func.hpp"
//#include <emscripten.h>

SDL_Window* main_window = SDL_CreateWindow("game", 1440+10, 10, 800, 600, 0);
SDL_Renderer* main_renderer = SDL_CreateRenderer(main_window, -1, 0);
SDL_Event main_event;
std::vector<Tile> main_array;
Player main_player;

int record=0;
void main_loop(){
	while(1){
		bool main_c=false;
		ClearRender(main_renderer);
		while(SDL_PollEvent(&main_event)){
			if(main_event.type == SDL_QUIT){

				//emscripten_cancel_main_loop();
				return;
			}
			record = GetTile(main_array);
			if(main_event.type == SDL_MOUSEBUTTONDOWN){
				//PutTile(arr, Tile::Type::EXIT);
				//p.Jump(j,1,arr);
				auto t = main_player.Move(main_array, main_renderer, record);
				if(t != 0) break; 
				main_c=true;
			}
		}
		main_player.ShowTiles(main_renderer);
		for(auto &t : main_array){
			t.Draw(main_renderer);
		}
		main_array.at(record).Highlight(main_renderer);

		if(main_c){
			//SDL_Delay(500);
			main_c=false;
		}
		main_player.Draw(main_renderer);
		SDL_RenderPresent(main_renderer);
	}
}

int main(){
	ResetMap(main_array, main_renderer);
	main_player.LoadTxt(main_renderer);
	Tile::LoadTexture(main_renderer);
	main_loop();

	//emscripten_set_main_loop_arg(main_loop, &i, -1, 1);

	//main_loop();
}
