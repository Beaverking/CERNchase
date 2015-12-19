#ifndef GAME_H
#define GAME_H

#include "App.h"
#include "Obstacle.h"
#include "Image.h"
#include "Text.h"

#define MAX_DISTANCE 64
#define MAX_GAME_OBJECTS 128
#define INIT_SPAWN_TIMER 1000
#define INIT_SPAWN_COUNT 1

#define MAX_OBSTACLES_IN_ROW 10
#define INIT_PLAYER_SPEED 0.005f
#define OBJECT_MIN_SCALE 0.1f
#define SIDE_CAP_WIDTH 50.0f
#define START_Y 340
#define OBJECT_SIDE_SPEED 0.6f
#define STEER_POWER 0.8f

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
		STATE_RIDE,
	};

	struct ObjectRow
	{
		void Update(uint32_t dt, float steer);

		std::vector<std::shared_ptr<Obstacle>> objects;
		float distance;;
	};


	void OnEvent(SDL_Event *evt);	//Handles input event from SDL

	void Update(uint32_t dt);
	void Draw(SDL_Renderer *renderer);

	void Reset();		//Restarts the game from beginning

	void SpawnNewRow();
	void StepRow();

private:
	std::shared_ptr<Image> splashImage;
	std::shared_ptr<Image> rideBg;
	std::shared_ptr<Image> treeImg;

	std::shared_ptr<Text> splashText1;
	std::shared_ptr<Text> splashText2;
	std::shared_ptr<Text> splashText3;
	std::shared_ptr<Text> splashText4;
	std::shared_ptr<Text> splashHint;

	ObjectRow* rows [MAX_DISTANCE];

	uint32_t nextSpawnTime;
	int nextSpawnCount;

	GameState currentState;
};

}

#endif