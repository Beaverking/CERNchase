#ifndef GAME_H
#define GAME_H

#include "App.h"

class Image;
class Text;

namespace CERNchase
{

//This class controls the logic of the game. Manages input, game states, game objects, score, etc.
class Game
{
public:
	Game();
	~Game();

	enum class GameState
	{
		STATE_INIT,
		STATE_SPLASH,
	};


	void OnEvent(SDL_Event *evt);	//Handles input event from SDL

	void Update(float dt);
	void Draw(SDL_Renderer *renderer);

	void Reset();		//Restarts the game from beginning

private:
	std::shared_ptr<Image> splashImage;

	std::shared_ptr<Text> splashText1;
	std::shared_ptr<Text> splashText2;
	std::shared_ptr<Text> splashText3;
	std::shared_ptr<Text> splashText4;
	std::shared_ptr<Text> splashHint;

	GameState currentState;
};

}

#endif