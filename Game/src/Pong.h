#pragma once
#include "Game.h"
#include "../gameEngine.h"

class PongGame : public Game
{

private:
	// Paddles
	static const int PADDLE_WIDTH = 1;
	static const int PADDLE_HEIGHT = 3;
	float paddle1velocity = 0;
	float paddle1y = 3;
	float paddle2velocity = 0;
	float paddle2y = 3;

	// Ball
	int ballX = 16;
	int ballY = 4;
	int ballXdir = 1;
	int ballYdir = 1;
	float timeBetweenMoves = 0.1;
	float timeSinceLastMove;
	void Draw(Engine & engine);

	// Score
	short int player1score = 0;
	short int player2score = 0;

public:
	PongGame();
	virtual void updateLoop(Engine &);
};