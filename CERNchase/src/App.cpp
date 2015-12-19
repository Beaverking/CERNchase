#include "App.h"
#include "Game.h"
#include "Image.h"
//#include "Animation.h"

namespace CERNchase
{

bool App::Init()
{
	//init SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	if(TTF_Init() != 0)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);

	//creating window
	window = SDL_CreateWindow("Test window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(window == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	//creating renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	//loading fonts
	loadedFonts["font_main"] = TTF_OpenFont("../data/kongtext.ttf", 16);
	loadedFonts["font_hint"] = TTF_OpenFont("../data/kongtext.ttf", 12);
	//loadedFonts["font_number"] = TTF_OpenFont("pixel.ttf", 18);		//numbers for score and life count
	//loadedFonts["font_message"] = TTF_OpenFont("pixel.ttf", 32);	//game over and other messages

	//loading images
	loadedImages["splash"] = std::make_shared<Image>("../data/splash.png");
	loadedImages["rideBg"] = std::make_shared<Image>("../data/gameScreen.png");
	loadedImages["tree1"] = std::make_shared<Image>("../data/tree1.png");

	//creating game
	game = std::make_shared<Game>();
	return true;
}

void App::Start()
{
	//main loop
	uint32_t currentTime = SDL_GetTicks();
	uint32_t acc = 0;
	while(!exit)
	{
		uint32_t newTime = SDL_GetTicks();
		uint32_t frameTime = newTime - currentTime;
		currentTime = newTime;
		acc += frameTime;

		while (acc > FRAME_TIME)
		{
			game->Update(FRAME_TIME);
			acc -= FRAME_TIME;
		}

		SDL_Event evt;
		while(SDL_PollEvent(&evt))
		{
			if(evt.type == SDL_QUIT)
			{
				exit = true;
			}
			else
			{
				game->OnEvent(&evt);
			}
		}

		SDL_RenderClear(renderer);
		game->Draw(renderer);

		SDL_RenderPresent(renderer);
		SDL_Delay(1);
	}
	Deinit();
}

std::shared_ptr<Image> App::GetImage(const std::string &name)
{
	std::map<std::string, std::shared_ptr<Image>>::iterator i = loadedImages.find(name);
	if (i != loadedImages.end())
		return i->second;
	return nullptr;
}

TTF_Font* App::GetFont(const std::string &name)
{
	std::map<std::string, TTF_Font*>::iterator fontI = loadedFonts.find(name);
	if (fontI != loadedFonts.end())
		return fontI->second;
	return nullptr;
}

void App::Deinit()
{
	//releasing fonts
	for(auto f_i = loadedFonts.begin(); f_i != loadedFonts.end(); f_i++)
	{
		TTF_CloseFont(f_i->second);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	TTF_Quit();
	IMG_Quit();
}

}