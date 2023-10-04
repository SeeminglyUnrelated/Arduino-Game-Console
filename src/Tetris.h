#pragma once
#include "Game.h"
#include "../gameEngine.h"

class TetrisGame : public Game
{
	private:
		int score; // In lines of blocks cleared

		// Define the dimensions of the game board
		static const int BOARD_WIDTH = 8;
		static const int BOARD_HEIGHT = 32;

		// Define the game board as a 2D array
		int gameBoard[BOARD_HEIGHT][BOARD_WIDTH] = {0};

	public:
		TetrisGame();
		virtual void updateLoop(Engine &);
};