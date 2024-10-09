#pragma once
#include "Game.h"
#include "../gameEngine.h"

class DinoGame : public Game
{

private:
	void Draw(Engine &engine);

    int dinoImage[25] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0};
    int cactusImage[4] = {1, 1, 1, 1};

    int dinoX = 3;

public:
	DinoGame();
	virtual void updateLoop(Engine &);
};