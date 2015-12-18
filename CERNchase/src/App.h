#ifndef APP_H
#define APP_H

#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <memory>
#include <map>
#include <algorithm>
#include <vector>
#include <list>
#include <random>
#include <ctime>
#include <fstream>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720
#define FRAME_TIME 16

namespace CERNchase
{

class Game;
class Image;
class Text;

enum class DrawPivot
{
	LEFT_UP,
	CENTER,
	CENTER_BOTTOM
};


//Helper struct to deal with 2d coordinates
struct Vec2
{
	Vec2(float _x, float _y) : x(_x), y(_y) {}
	Vec2(int _x, int _y) : x(_x), y(_y) {}
	Vec2() : x(0.0f), y(0.0f) {}

	void Normalize() { float inv = 1.0f / sqrtf(x * x + y * y); x *= inv; y *= inv; }

	Vec2 operator +(const Vec2 &v) const { return Vec2(x + v.x, y + v.y); }
	Vec2 operator +=(const Vec2 &v) { x += v.x; y += v.y; return Vec2(x, y); }
	Vec2 operator -(const Vec2 &v) const { return Vec2(x - v.x, y - v.y); }
	Vec2 operator -=(const Vec2 &v) { x -= v.x; y -= v.y; return Vec2(x, y); }
	Vec2 operator *(float f) const { return Vec2(x * f, y * f); }
	Vec2 operator *=(float f) { x *= f; y *= f; return Vec2(x, y); }

	bool operator ==(const Vec2 &other) const { return x == other.x && y == other.y; }
	bool operator !=(const Vec2 &other) const { return x != other.x || y != other.y; }

	float x, y;
};

//Main application class. Uses singletone to ensure we have only one app at the time.
class App
{
public:
	static App* Instance()
	{
		static App inst;
		return &inst;
	}

	static float RandomRange(float min, float max)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		float diff = fabsf(max - min);
		float add = rnd * diff;
		return std::min(min, max) + add;
	}

	bool Init();
	void Deinit();
	void Start();
	SDL_Renderer *GetRenderer() const { return renderer; }
	Game *GetGame() const { return game.get(); }
	std::shared_ptr<Image> GetImage(const std::string &name);
	TTF_Font *GetFont(const std::string &name);

protected:
	virtual ~App() {};

private:
	App(): window(nullptr), renderer(nullptr), exit(false) {};
	App(const App &);
	void operator = (const App &);

	SDL_Window *window;			//Main application window
	SDL_Renderer *renderer;		//Renderer to be able to draw things

	std::shared_ptr<Game> game;	//Game logic implemented here

	std::map<std::string, std::shared_ptr<Image>> loadedImages;		//All image resources for the game stored here.
	std::map<std::string, TTF_Font *> loadedFonts;					//released in Deinit()

	bool exit;
};

}

#endif