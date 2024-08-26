#pragma once
#include "blx/Defines.h"
#include "BLX/blx_gameType.h"
#include "BLX/Camera.h"

typedef struct{
    float deltaTime;
    Camera mainCam;
    blxModel currentModel;
}gameState;

blxBool InitGame(blxGameInstance* gameInstance);

blxBool UpdateGame(float deltaTime);

blxBool Render();