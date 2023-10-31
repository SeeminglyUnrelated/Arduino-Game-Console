#include "Tetris.h"
#include "Arduino.h"
#include "../gameEngine.h"

TetrisGame::TetrisGame()
{
	SpawnBlock();
}

void TetrisGame::updateLoop(Engine & engine)
{

}

void SpawnBlock()
{
	posx = random(0, 7)
	blocks.push_back(new Vector2())
}

void Draw()
{

}
