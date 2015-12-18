#include "Game.h"
#include "Image.h"
#include "Text.h"

namespace CERNchase
{

Game::Game()
{
	srand(static_cast<unsigned int>(time(NULL)));
	splashImage = App::Instance()->GetImage("splash");

	TTF_Font* gameFont = App::Instance()->GetFont("font_main");
	TTF_Font* hintFont = App::Instance()->GetFont("font_hint");

	SDL_Color textCol;
	textCol.a = 255;
	textCol.r = 255;
	textCol.g = 255;
	textCol.b = 60;

	SDL_Color hintCol;
	textCol.a = 255;
	textCol.r = 255;
	textCol.g = 255;
	textCol.b = 180;

	splashText1 = std::make_shared<Text>();
	splashText1->SetText(gameFont, "Hurry! it's almost Christmas now", textCol);
	splashText2 = std::make_shared<Text>();
	splashText2->SetText(gameFont, "but scientists working in LHC", textCol);
	splashText3 = std::make_shared<Text>();
	splashText3->SetText(gameFont, "didn't get their presents yet.", textCol);
	splashText4 = std::make_shared<Text>();
	splashText4->SetText(gameFont, "Make sure everyone is happy this year!", textCol);

	splashHint= std::make_shared<Text>();
	splashHint->SetText(hintFont, "Hit 'space' to begin", hintCol);

	currentState = GameState::STATE_SPLASH;
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
	if (currentState == GameState::STATE_SPLASH)
	{
		splashImage->Draw(renderer, Vec2(0.0f, 0.0f));
		splashText1->Draw(renderer, Vec2(520, 450));
		splashText2->Draw(renderer, Vec2(520, 480));
		splashText3->Draw(renderer, Vec2(520, 510));
		splashText4->Draw(renderer, Vec2((SCREEN_WIDTH - splashText4->GetSize().x) * 0.5f, 640.0f));
		splashHint->Draw(renderer, Vec2((SCREEN_WIDTH - splashHint->GetSize().x) * 0.5f, 660.0f));
	}
}

void Game::OnEvent(SDL_Event *evt)
{
	switch (evt->type)
	{
	case SDL_KEYUP:
		break;
	}
}

}

