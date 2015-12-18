#include "Image.h"

namespace CERNchase
{

Image::Image(const char* path)
{
	imageTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path);
	if (!loadedSurface)
		printf("[ERROR]: failed to load image file %s", path);
	else
	{
		imageTexture = SDL_CreateTextureFromSurface(App::Instance()->GetRenderer(), loadedSurface);
		if (!imageTexture)
			printf("[ERROR]: failed to create texture from surface: %s, %s", path, SDL_GetError());
		SDL_FreeSurface(loadedSurface);
	}
	pivot = DrawPivot::LEFT_UP;
	int w;
	int h;
	if (imageTexture)
	{
		SDL_QueryTexture(imageTexture, NULL, NULL, &w, &h);
		textureSize.x = static_cast<float>(w);
		textureSize.y = static_cast<float>(h);
	}
}

Image::~Image()
{
	if (imageTexture)
	{
		SDL_DestroyTexture(imageTexture);
		imageTexture = nullptr;
	}
}

void Image::Draw(SDL_Renderer* renderer, const Vec2& position)
{
	float x = position.x;
	float y = position.y;
	if (pivot == DrawPivot::CENTER)
	{
		x -= textureSize.x * 0.5f;
		y -= textureSize.y * 0.5f;
	}
	else if (pivot == DrawPivot::CENTER_BOTTOM)
	{
		x -= textureSize.x * 0.5f;
		y -= textureSize.y;
	}
	SDL_Rect distRect;
	distRect.x = static_cast<int>(floorf(x + 0.5f));
	distRect.y = static_cast<int>(floorf(y + 0.5f));
	distRect.w = static_cast<int>(floorf(textureSize.x + 0.5f));
	distRect.h = static_cast<int>(floorf(textureSize.y + 0.5f));
	SDL_RenderCopyEx(renderer, imageTexture, NULL, &distRect, 0.0f, NULL, SDL_FLIP_NONE);
}

void Image::Draw(SDL_Renderer* renderer, const Vec2& position, float scale)
{
	float x = position.x;
	float y = position.y;
	if (pivot == DrawPivot::CENTER)
	{
		x -= textureSize.x * 0.5f * scale;
		y -= textureSize.y * 0.5f * scale;
	}
	else if (pivot == DrawPivot::CENTER_BOTTOM)
	{
		x -= textureSize.x * 0.5f * scale;
		y -= textureSize.y * scale;
	}
	SDL_Rect distRect;
	distRect.x = static_cast<int>(floorf(x + 0.5f));
	distRect.y = static_cast<int>(floorf(y + 0.5f));
	distRect.w = static_cast<int>(floorf(textureSize.x * scale + 0.5f));
	distRect.h = static_cast<int>(floorf(textureSize.y * scale + 0.5f));
	SDL_RenderCopyEx(renderer, imageTexture, NULL, &distRect, 0.0f, NULL, SDL_FLIP_NONE);
}

//void Image::Draw(SDL_Renderer* renderer, const Vec2& position, float angle)
//{
//	float x = position.x;
//	float y = position.y;
//	if (pivot == DrawPivot::CENTER)
//	{
//		x -= textureSize.x * 0.5f;
//		y -= textureSize.y * 0.5f;
//	}
//	else if (pivot == DrawPivot::CENTER_BOTTOM)
//	{
//		x -= textureSize.x * 0.5f;
//		y -= textureSize.y;
//	}
//	SDL_Rect distRect;
//	distRect.x = static_cast<int>(floorf(x + 0.5f));
//	distRect.y = static_cast<int>(floorf(y + 0.5f));
//	distRect.w = static_cast<int>(floorf(textureSize.x + 0.5f));
//	distRect.h = static_cast<int>(floorf(textureSize.y + 0.5f));
//	SDL_Point r;
//	r.x = static_cast<int>(x);
//	r.y = static_cast<int>(y);
//
//	SDL_RenderCopyEx(renderer, imageTexture, NULL, &distRect, static_cast<double>(angle), &r, SDL_FLIP_NONE);
//}

}