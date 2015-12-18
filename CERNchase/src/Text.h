#ifndef TEXT_H
#define TEXT_H

#include "App.h"

namespace CERNchase
{

class Text
{
public:
	Text();
	~Text();

	void SetText(TTF_Font* font, const char* text, SDL_Color& color);
	void Draw(SDL_Renderer* renderer, Vec2& position);
	inline const Vec2 GetSize() const { return textSize; }

private:
	SDL_Texture* textTexture;
	Vec2 textSize;
};

}

#endif