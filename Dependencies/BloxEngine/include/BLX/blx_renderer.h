#pragma once
#include "Defines.h"
#include "Transform.h"
#include "cglm/cglm.h"
#include "utils/blx_vlist.h"

typedef enum GraphicsAPI {
    OPENGL
};

typedef struct {
    vec3 position;
    vec3 normal;
    vec2 uv;
}blxVertex;

typedef blxVertex vList_blxVertex;

typedef struct {
    vList_blxVertex* vertices;
    unsigned int* indices;
    Transform transform;
}blxMesh;



BLXAPI void blxInitRenderer();
BLXAPI void blxDraw(blxMesh* mesh);
BLXAPI void blxMeshData(blxMesh* mesh, unsigned int vertCount, unsigned int uvCount);




