#include "Pong.h"
#include "Arduino.h"
#include "../gameEngine.h"

PongGame::PongGame()
{
	timeSinceLastMove = 0;
	player1score = 0;
	player2score = 0;
	ballX = 16;
	ballY = 4;
}

void PongGame::updateLoop(Engine &engine)
{
	timeSinceLastMove += engine.deltaTime;

	if (timeSinceLastMove > timeBetweenMoves)
	{
		// Move Ball & paddles
		timeSinceLastMove = timeSinceLastMove - timeBetweenMoves;

		ballX += ballXdir;
		ballY += ballYdir;

		if (ballY <= 0 || ballY >= 8 - 1)
		{
			ballYdir = -ballYdir;
		}

		// Move paddles
		paddle1y += engine.Joystick1.y;
		paddle2y += engine.Joystick2.y;

		// COLLISION
		// Paddle collision with walls
		if (paddle1y < 0)
			paddle1y = 0;
		else if (paddle1y > 5)
			paddle1y = 5;
		if (paddle2y < 0)
			paddle2y = 0;
		else if (paddle2y > 7)
			paddle2y = 5;

		// Check for ball collisions with paddles
		if (ballX == 8 && ballY >= paddle1y && ballY < paddle1y + PADDLE_HEIGHT)
		{
			//Serial.println("Collision with left paddle");
			ballXdir = -ballXdir; // Reverse X velocity for bouncing off left paddle
		}
		else if (ballX == 24 - 1 && ballY >= paddle2y && ballY < paddle2y + PADDLE_HEIGHT)
		{
			//Serial.println("Collision with right paddle");
			ballXdir = -ballXdir; // Reverse X velocity for bouncing off right paddle
		}

		// Ball out of bounds (scoring condition)
		if (ballX < 8)
		{
			player2score++;
			// Reset ball position and velocities
			ballX = 16;
			ballY = 4;
			ballXdir = -ballXdir; // Reverse ball's horizontal direction
		} 
		else if (ballX >= 24)
		{
			player1score++;
			ballX = 16;
			ballY = 4;
			ballXdir = -ballXdir;
		}
	}

	Draw(engine);
}

void PongGame::Draw(Engine & engine)
{
	// Draw ball
	engine.setPixel(ballX, ballY, true);

	// Draw Paddles
	for (int i = 0; i <= PADDLE_HEIGHT - 1; i++)
	{
		engine.setPixel(8, i + paddle1y, true);
		engine.setPixel(23, i + paddle2y, true);
	}

	// Draw Score
	for (int i = 0; i < player2score; i++)
	{
		engine.lc.setRow(0, i, 0b11111111);
	}
	for (int i = 0; i < player1score; i++)
	{
		engine.lc.setRow(3, i, 0b11111111);
	}
}