#ifndef IMAGE_H
#define IMAGE_H

#include "App.h"

namespace CERNchase
{

class Image
{
public:
	Image(const char* path);
	~Image();

	void Draw(SDL_Renderer* renderer, const Vec2& position);
	void Draw(SDL_Renderer* renderer, const Vec2& position, float scale);
	//void Draw(SDL_Renderer* renderer, const Vec2& position, float angle);
	inline void SetPivot(DrawPivot drawPivot) { pivot = drawPivot; }

private:
	SDL_Texture* imageTexture;
	DrawPivot pivot;
	Vec2 textureSize;
};

}

#endif