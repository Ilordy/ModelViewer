#pragma once
#include "core/blx_transform.h"
#include <cglm/cam.h>
#include <cglm/cglm.h>

typedef enum { PERSPECTIVE = 0, ORTHOGRAPHIC = 1 } CameraProjectionType;

typedef struct {
  float fov;
  Transform transform;
  CameraProjectionType projectionType;
  mat4 projecionMatrix, viewMatrix;
} Camera;

void _blxGetCameraProjection(Camera* cam, CameraProjectionType projType, mat4 dest);

BLXAPI void camera_init(Camera* cam, float fov);
BLXAPI void camera_setProjection(Camera* cam, CameraProjectionType projType);
BLXAPI void camera_update(Camera* cam);
