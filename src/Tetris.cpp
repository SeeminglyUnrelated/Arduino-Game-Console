#include "Tetris.h"
#include "Arduino.h"
#include "../gameEngine.h"

TetrisGame::TetrisGame()
{
	current.x = 4;
	current.y = 0;
	current.type = 0;
	current.rotate = 0;
}

void TetrisGame::updateLoop(Engine & engine)
{
	TetrisGame::SpawnBlock(current, false);
	TetrisGame::Draw(engine);
}

bool TetrisGame::SpawnBlock(STATUS s, bool action = false)
{
	if (board[s.x][s.y] != 0)
	{
		return false;
	}

	if (action)
	{
		board[s.x][s.y] = s.type;
	}

	for (int i = 0; i < 3; i++)
	{
		int dx = block[s.type].p[i].x;
		int dy = block[s.type].p[i].y;
		int r = s.rotate % block[s.type].rotate;
		for (int j = 0; j < r; j++)
		{
			int nx = dx, ny = dy;
			dx = ny;
			dy = -nx;
		}
		if (board[s.x + dx][s.y + dy] != 0)
		{
			return false;
		}
		if (action)
		{
			board[s.x + dx][s.y + dy] = s.type;
		}
	}
	if (!action)
	{
		TetrisGame::SpawnBlock(s, true);
	}
	return true;
}

void TetrisGame::Draw(Engine & engine)
{
	for (int[8] x : board)
	{
		for (int y : x)
		{
			if (board[x][y] == 0) {continue;}
			engine.setPixel(x, y, true);
		}
	}
}