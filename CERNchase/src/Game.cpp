#include "Game.h"

Game::Game()
{
	//srand(time(NULL));
}

Game::~Game()
{
}

void Game::Reset()
{
}

void Game::Update(float dt)
{
	//updating player input
	const Uint8 *keyState = SDL_GetKeyboardState(NULL);
}

void Game::Draw(SDL_Renderer *renderer)
{
	
}

void Game::OnEvent(SDL_Event *evt)
{
	switch (evt->type)
	{
	case SDL_KEYUP:
		break;
	}
}

