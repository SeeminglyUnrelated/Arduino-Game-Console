#include "SpaceGame.h"
#include "Arduino.h"

SpaceGame::SpaceGame()
{
	playerPos.x = 1;
	playerPos.y = 4;
	timeToNextEnemySpawn = 1;
	numEnemies = 0;
	numBullets = 0;
	elapsedTime = 0;
	gameOver = false;
	lastShootTime = 0;
	numEnemiesDestroyed = 0;
	scoreDisplayAmount = -5;
}

void SpaceGame::updateLoop(Engine &engine)
{

	if (gameOver)
	{
		scoreDisplayAmount += engine.deltaTime * 10;
		for (int i = 0; i < min(numEnemiesDestroyed, (int)scoreDisplayAmount); i++)
		{
			int x = i % 16;
			int y = i / 16;
			engine.setPixel(x, y, true);
		}
		return;
	}
	elapsedTime += engine.deltaTime;

	// Move player
	playerPos.y += engine.deltaTime * playerSpeed * engine.Joystick1y;
	if (playerPos.y >= 8)
	{
		playerPos.y = 0;
	}
	else if (playerPos.y < 0)
	{
		playerPos.y = 7.99;
	}

	// Draw player
	int playerCoordX = (int)playerPos.x;
	int playerCoordY = (int)playerPos.y;
	engine.setPixel(playerCoordX, playerCoordY, true);
	engine.setPixel(playerCoordX - 1, playerCoordY, true);
	engine.setPixel(playerCoordX - 1, playerCoordY - 1, true);
	engine.setPixel(playerCoordX - 1, playerCoordY + 1, true);

	// Shoot
	if (engine.buttonDownThisFrame && (elapsedTime - lastShootTime) > delayBetweenShots)
	{
		lastShootTime = elapsedTime;
		bullets[numBullets].x = playerPos.x + 1;
		bullets[numBullets].y = playerPos.y;
		numBullets++;
	}

	// Update and draw bullets
	for (int i = numBullets - 1; i >= 0; i--)
	{
		engine.setPixel((int)bullets[i].x, (int)bullets[i].y, true);
		bullets[i].x += engine.deltaTime * 20;

		bool destroyBullet = bullets[i].x >= engine.m_totalWidth;

		// Check for collision with enemies
		for (int j = numEnemies - 1; j >= 0; j--)
		{
			if (bullets[i].x >= enemies[j].x && (int)bullets[i].y == (int)enemies[j].y)
			{
				destroyBullet = true;
				// Destroy enemy (put end enemy into current slot to keep active enemies in front)
				numEnemies--;
				enemies[j].x = enemies[numEnemies].x;
				enemies[j].y = enemies[numEnemies].y;
				numEnemiesDestroyed++;
				break;
			}
		}

		// bullet off screen, recycle
		if (destroyBullet)
		{
			numBullets--;
			// put end bullet into current slot to keep 'alive' bullets in front
			bullets[i].x = bullets[numBullets].x;
			bullets[i].y = bullets[numBullets].y;
		}
	}

	// Handle enemy spawning
	timeToNextEnemySpawn -= engine.deltaTime;
	if (timeToNextEnemySpawn <= 0)
	{
		float difficultyPercent = min(1, elapsedTime / difficultyDuration);
		float randomSeconds = .5;
		float randomT = (random(randomSeconds * 10) - randomSeconds * 5) / (randomSeconds * 5);
		timeToNextEnemySpawn = spawnDelayStart + (spawnDelayEnd - spawnDelayStart) * difficultyPercent + randomT;

		enemies[numEnemies].x = engine.m_totalWidth - 1;
		enemies[numEnemies].y = random(0, 8);
		numEnemies++;
	}

	// Update and draw enemies
	for (int i = numEnemies - 1; i >= 0; i--)
	{
		engine.setPixel((int)enemies[i].x, (int)enemies[i].y, true);

		// Player - enemy collision check
		int enemyCoordX = (int)enemies[i].x;
		int enemyCoordY = (int)enemies[i].y;
		bool collision = enemyCoordX == playerCoordX && enemyCoordY == playerCoordY;
		collision |= enemyCoordX == playerCoordX - 1 && enemyCoordY == playerCoordY - 1;
		collision |= enemyCoordX == playerCoordX - 1 && enemyCoordY == playerCoordY + 1;
		if (collision)
		{
			gameOver = true;
			break;
		}

		// Move
		enemies[i].x -= engine.deltaTime * 5;

		// ennemy off screen, recycle
		if (enemies[i].x < 0)
		{
			numEnemies--;
			// put end enemy into current slot to keep active enemies in front
			enemies[i].x = enemies[numEnemies].x;
			enemies[i].y = enemies[numEnemies].y;
		}
	}
}