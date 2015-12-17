#ifndef GAME_H
#define GAME_H

#include "App.h"

//This class controls the logic of the game. Manages input, game states, game objects, score, etc.
class Game
{
public:
	Game();
	~Game();

	void OnEvent(SDL_Event *evt);	//Handles input event from SDL

	void Update(float dt);
	void Draw(SDL_Renderer *renderer);

	void Reset();		//Restarts the game from beginning

private:
};

#endif