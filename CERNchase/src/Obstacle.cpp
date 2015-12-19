#include "Obstacle.h"
#include "Image.h"
#include "Game.h"

namespace CERNchase
{

Obstacle::Obstacle()
{
	SetType(ObstacleType::Obstacle_Tree);
	active = false;
	distance = MAX_DISTANCE;
}

void Obstacle::Update(uint32_t dt)
{

}

void Obstacle::Draw(SDL_Renderer* renderer)
{
	sprite->Draw(renderer, position, currScale);
}

void Obstacle::SetType(ObstacleType newType)
{
	if (type == newType)
		return;
	type = newType;
	if (newType == ObstacleType::Obstacle_Tree)
	{
		sprite = App::Instance()->GetImage("tree1");
		sprite->SetPivot(DrawPivot::CENTER_BOTTOM);
	}
}

}