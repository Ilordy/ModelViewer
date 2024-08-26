#pragma once
#include "Defines.h"
#include "Camera.h"
#include "blx_mesh.h"
#include "blx_model.h"

typedef enum {
    OPENGL
}GraphicsAPI;

typedef struct
{
    Camera* cam;
    blxModel models[5];
    unsigned int modelCount;
}blxRenderPacket;

typedef enum {
    BLX_SHADING_SOLID,
    BLX_SHADING_WIREFRAME
}blxShadingMode;

BLXAPI void blxDrawModel(blxModel* model);
BLXAPI void blxInitRenderer(GraphicsAPI graphicsToUse);
BLXAPI void blxInitMesh(blxMesh* mesh);
BLXAPI void blxSetShadingMode(blxShadingMode mode);

// TODO: THIS is temp for now for in the future of support more than 1 camera.
BLXAPI void blxAddCameraToRender(Camera* cam);

BLXAPI void blxDraw();
BLXAPI void blxUpdateMesh(blxMesh* mesh);
BLXAPI void blxImportMesh(const char* filePath, blxMesh* outMesh);




