#include "Text.h"

namespace CERNchase
{

Text::Text()
{
	textTexture = nullptr;
}

Text::~Text()
{
	if (textTexture)
		SDL_DestroyTexture(textTexture);
	textTexture = nullptr;
}

void Text::SetText(TTF_Font* font, const char* text, SDL_Color& color)
{
	if (textTexture)
		SDL_DestroyTexture(textTexture);
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
	textTexture = SDL_CreateTextureFromSurface(App::Instance()->GetRenderer(), textSurface);
	int w;
	int h;
	if (textTexture)
	{
		SDL_QueryTexture(textTexture, NULL, NULL, &w, &h);
		textSize.x = static_cast<float>(w);
		textSize.y = static_cast<float>(h);
	}
}

void Text::Draw(SDL_Renderer* renderer, Vec2& position)
{
	float x = position.x;
	float y = position.y;
	SDL_Rect distRect;
	distRect.x = static_cast<int>(floorf(x + 0.5f));
	distRect.y = static_cast<int>(floorf(y + 0.5f));
	distRect.w = static_cast<int>(floorf(textSize.x + 0.5f));
	distRect.h = static_cast<int>(floorf(textSize.y + 0.5f));
	SDL_RenderCopyEx(renderer, textTexture, NULL, &distRect, 0.0f, NULL, SDL_FLIP_NONE);
}

}