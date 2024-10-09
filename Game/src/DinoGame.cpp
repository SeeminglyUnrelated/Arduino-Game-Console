#include "DinoGame.h"
#include "Arduino.h"
#include "../gameEngine.h"

DinoGame::DinoGame()
{
}

void DinoGame::updateLoop(Engine &engine)
{
    if (engine.Joystick1.buttonDownThisFrame && dinoX == 3)
    {
        dinoX += 2;
    }


    if (dinoX > 3)
        dinoX--;
    if (dinoX < 3)
        dinoX = 3;

	Draw(engine);
}

void DinoGame::Draw(Engine & engine)
{
    engine.drawImage(dinoImage, 5, 5, 2, dinoX);
}