#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "App.h"

namespace CERNchase
{

class Image;

class Obstacle
{
public: 

	enum class ObstacleType
	{
		Obstacle_Tree,
	};

	Obstacle();

	void Update(uint32_t dt);
	void Draw(SDL_Renderer* renderer);
	void SetType(ObstacleType newType);

	std::shared_ptr<Image> sprite;
	float currScale;
	Vec2 position;
	int distance;
	float horizPosition;
	bool active;

	ObstacleType type;
};

}

#endif