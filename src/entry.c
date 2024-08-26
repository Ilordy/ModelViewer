#include "BLX/blx_entry.h"
#include "game.h"

blxBool blxCreateGame(blxGameInstance* outGame) {
  outGame->config.graphicAPI = OPENGL;
  outGame->config.width = 960;
  outGame->config.height = 540;
  outGame->config.name = "Model Viewer";
  outGame->Init = InitGame;
  outGame->Update = UpdateGame;
  outGame->Render = Render;
  return BLX_TRUE;
}