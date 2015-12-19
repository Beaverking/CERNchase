#include "Game.h"


namespace CERNchase
{

Game::Game()
{
	srand(static_cast<unsigned int>(time(NULL)));
	splashImage = App::Instance()->GetImage("splash");
	rideBg = App::Instance()->GetImage("rideBg");
	treeImg = App::Instance()->GetImage("tree1");

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

	for (int i = 0; i < MAX_DISTANCE; i++)
	{
		rows[i] = new ObjectRow();
		rows[i]->objects.reserve(MAX_OBSTACLES_IN_ROW);
		rows[i]->distance = static_cast<float>(MAX_DISTANCE - i);
		for (int j = 0; j < MAX_OBSTACLES_IN_ROW; j++)
		{
			rows[i]->objects.push_back(std::make_shared<Obstacle>());
			rows[i]->objects.back()->SetType(Obstacle::ObstacleType::Obstacle_Tree);
		}
	}
}

Game::~Game()
{
	for (int i = 0; i < MAX_DISTANCE; i++)
	{
		delete rows[i];
	}
}

void Game::Reset()
{
}

void Game::Update(uint32_t dt)
{
	//updating player input
	const Uint8 *keyState = SDL_GetKeyboardState(NULL);
	if (currentState == GameState::STATE_SPLASH)
	{
		if (keyState[SDL_SCANCODE_SPACE])
		{
			currentState = GameState::STATE_RIDE;
			nextSpawnTime = INIT_SPAWN_TIMER;
			nextSpawnCount = INIT_SPAWN_COUNT;
			SpawnNewRow();
		}
	}
	else if (currentState == GameState::STATE_RIDE)
	{
		float steerPower = 0.0f;
		if (keyState[SDL_SCANCODE_LEFT] && !keyState[SDL_SCANCODE_RIGHT])
			steerPower = STEER_POWER;
		else if (keyState[SDL_SCANCODE_RIGHT] && !keyState[SDL_SCANCODE_LEFT])
			steerPower = -STEER_POWER;
		bool swap = false;
		for (int i = 0; i < MAX_DISTANCE; i++)
		{
			int oldDist = floorf(rows[i]->distance);
			rows[i]->Update(dt, steerPower);
			if (floorf(rows[i]->distance) == 0)
				swap = true;
		}
		if (swap)
			StepRow();
	}
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
	else if (currentState == GameState::STATE_RIDE)
	{
		rideBg->Draw(renderer, Vec2(0.0f, 0.0f));
		for (int i = 0; i < MAX_DISTANCE; i++)
		{
			for (int j = 0; j < MAX_OBSTACLES_IN_ROW; j++)
			{
				if (!rows[i]->objects[j]->active)
					continue;
				rows[i]->objects[j]->Draw(renderer);
			}
		}
	}
}

void Game::SpawnNewRow()
{
	if (App::RandomRange(0.0f, 1.0f) < 0.2f)
		nextSpawnCount = 1;
	else
		nextSpawnCount = 0;
	rows[0]->distance = static_cast<float>(MAX_DISTANCE);
	for (int i = 0; i < MAX_OBSTACLES_IN_ROW; i++)
	{
		if (i < nextSpawnCount)
		{
			rows[0]->objects[i]->active = true;
			rows[0]->objects[i]->horizPosition = App::RandomRange(0.0f, 1.0f);
			rows[0]->objects[i]->position.x = rows[0]->objects[0]->horizPosition * SCREEN_WIDTH;
			rows[0]->objects[i]->position.y = START_Y;
			rows[0]->objects[i]->currScale = OBJECT_MIN_SCALE;
		}
		else
			rows[0]->objects[i]->active = false;
	}

	nextSpawnTime = INIT_SPAWN_TIMER;
	nextSpawnCount = INIT_SPAWN_COUNT;
}

void Game::StepRow()
{
	ObjectRow* last = rows[MAX_DISTANCE - 1];
	for (int i = MAX_DISTANCE - 1; i > 0; i--)
		rows[i] = rows[i - 1];
	//check player collision here
	rows[0] = last;
	SpawnNewRow();
}

void Game::OnEvent(SDL_Event *evt)
{
	switch (evt->type)
	{
	case SDL_KEYUP:

		break;
	}
}

void Game::ObjectRow::Update(uint32_t dt, float steer)
{
	float dDist = INIT_PLAYER_SPEED * static_cast<float>(dt);
	float distCoef = 1.0f - distance / static_cast<float>(MAX_DISTANCE);
	distance -= dDist * (1.0f + distCoef * distCoef * distCoef);
	distCoef = 1.0f - distance / static_cast<float>(MAX_DISTANCE);
	for (int j = 0; j < MAX_OBSTACLES_IN_ROW; j++)
	{
		if (!objects[j]->active)
			continue;
		float sideCoef = (objects[j]->horizPosition - 0.5f) * 2.0;
		objects[j]->currScale = OBJECT_MIN_SCALE + distCoef * distCoef;
		objects[j]->position.y = START_Y + (distCoef * distCoef * static_cast<float>(SCREEN_HEIGHT - START_Y)) * 0.8f;
		objects[j]->position.x += sideCoef * OBJECT_SIDE_SPEED * dt * distCoef;
		objects[j]->position.x += steer * dt * (1.0f - distCoef) * 0.5;
	}
}

}

