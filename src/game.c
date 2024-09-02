#include "game.h"
#include "BLX/core/blx_logger.h"
#include "BLX/core/blx_input.h"
#include "BLX/rendering/blx_model.h"
#include "BLX/utils/blx_fileManagement.h"
#include "BLX/core/blx_memory.h"
#include "BLX/blx_imGui.h"

static gameState* state;

void ProcessMovement(float deltaTime);
void ProcessMouseMove(float deltaTime);

blxBool InitGame(blxGameInstance* gameInstance)
{
    BLXINFO("Application Starting...");

    state = (gameState*)blxAllocate(sizeof(gameState), BLXMEMORY_TAG_GAME);
    blxInitModel(&state->currentModel);
    state->currentModel.mesh.shader = shader_create("res/shaders/Standard.frag",
        "res/shaders/Standard.vert", BLX_TRUE);
    camera_init(&state->mainCam, 45);
    blxAddCameraToRender(&state->mainCam);

    //Temp for now.
    state->currentModel.mesh._meshData = NULL;
    state->mainCam.transform.position[2] = 10;
    // blxImGuiInit();
    return BLX_TRUE;
}

blxBool UpdateGame(float deltaTime)
{
    state->deltaTime = deltaTime;
    ProcessMovement(deltaTime);
    ProcessMouseMove(deltaTime);
    mat4 rot;
    glm_quat_mat4(state->currentModel.transform.rotation, rot);
    glm_rotate(rot, glm_rad(90) * deltaTime, Vec3_Up);
    //glm_mat4_quat(rot, state->currentModel.transform.rotation);
    if (blxInputGetKeyDown(BLX_KEY_E)) {
        char buffer[blxMaxFilePath];
        if (blxOpenFilePanel("Choose obj to load", NULL, ".obj", buffer)) {
            BLXDEBUG("%s", buffer);
            blxImportMesh(buffer, &state->currentModel.mesh);
        }
    }

    if (blxInputGetKeyDown(BLX_KEY_1)) {
        blxSetShadingMode(BLX_SHADING_SOLID);
    }
    if (blxInputGetKeyDown(BLX_KEY_2)) {
        blxSetShadingMode(BLX_SHADING_WIREFRAME);
    }

    return BLX_TRUE;
}


blxBool Render()
{
    // blxImGuiBtn();
    // Checking if mesh has been initialized by the renderer.
    // TODO: This should probably be handled by the engine itself.
    if (state->currentModel.mesh._meshData != NULL) {
        blxDrawModel(&state->currentModel);
    }
    return BLX_TRUE;
}

void ProcessMovement(float deltaTime)
{
    const float moveSpeed = 10 * deltaTime;
    Transform* camTrans = &state->mainCam.transform;

    if (blxInputGetKey(BLX_KEY_W))
    {
        vec3 forward;
        transform_forward(camTrans, forward);
        glm_vec3_muladds(forward, moveSpeed, camTrans);
    }

    if (blxInputGetKey(BLX_KEY_S))
    {
        vec3 forward;
        transform_forward(camTrans, forward);
        glm_vec3_negate(forward);
        glm_vec3_muladds(forward, moveSpeed, camTrans);
    }

    if (blxInputGetKey(BLX_KEY_A))
    {
        vec3 right;
        transform_right(camTrans, right);
        glm_vec3_muladds(right, moveSpeed, camTrans);
    }

    if (blxInputGetKey(BLX_KEY_D))
    {
        vec3 left;
        transform_right(camTrans, left);
        glm_vec3_negate(left);
        glm_vec3_muladds(left, moveSpeed, camTrans);
    }
}

void ProcessMouseMove(float deltaTime)
{
    if (!blxInputGetMouseButton(BLX_RMB)) {
        return;
    }

    static float xAngle, yAngle;
    const float sensitivity = 30 * deltaTime;

    int xPos, yPos;
    blxInputGetMousePos(&xPos, &yPos);

    int lastX, lastY;
    blxInputGetPrevMousePos(&lastX, &lastY);

    float xDelta = lastX - xPos;
    float yDelta = yPos - lastY; // reversed since y-coordinates range from bottom to top
    xDelta *= sensitivity;
    yDelta *= sensitivity;
    yAngle += glm_rad(yDelta);
    xAngle += glm_rad(xDelta);

    Quaternion xRot, yRot;
    glm_quatv(xRot, yAngle, Vec3_Right);
    glm_quatv(yRot, xAngle, Vec3_Up);
    glm_quat_mul(yRot, xRot, state->mainCam.transform.rotation);
}
