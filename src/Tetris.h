#pragma once
#include "Game.h"
#include "../gameEngine.h"
#include "Vector2.cpp"

class TetrisGame : public Game
{
	private:
		int board[8][32];

		typedef struct _TAG_POSITION
		{
			int x;
			int y;
		} POSITION;

		typedef struct _TAG_BLOCK
		{
			int rotate;
			POSITION p[3];
		} BLOCK;

		BLOCK block[8] = {
			{1, {{0, 0}, {0, 0}, {0, 0}}},	  // null
			{2, {{0, -1}, {0, 1}, {0, 2}}},	  // tetris
			{4, {{0, -1}, {0, 1}, {1, 1}}},	  // L1
			{4, {{0, -1}, {0, 1}, {-1, 1}}},  // L2
			{2, {{0, -1}, {1, 0}, {1, 1}}},	  // key1
			{2, {{0, -1}, {-1, 0}, {-1, 1}}}, // key2
			{1, {{0, 1}, {1, 0}, {1, 1}}},	  // square
			{4, {{0, -1}, {1, 0}, {-1, 0}}},  // T
		};

		typedef struct _TAG_STATUS
		{
			int x;
			int y;
			int type;
			int rotate;
		} STATUS;

		STATUS current;

		int score; // In lines of blocks cleared

		bool SpawnBlock(STATUS s, bool action = false);
		void CheckLines();
		void Draw(Engine & engine);

	public:
		TetrisGame();
		virtual void updateLoop(Engine &);
};