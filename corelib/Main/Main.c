/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "../Deccan.h"

bool DE_AppInit(DeccanSettings *settings) {
    DE_SDLInit();

    DE_RendererPreInit();
    DE_CoreInit(settings);
    DE_RendererCreate(DE_CoreGetWindow());

    DE_SceneSysCreate();

    DE_GenericPipelineCreate();

    return true;
}

void DE_AppUpdate(void) {
    DeccanTimer fpsTimer;
    DeccanTimer frmTimer;

    DE_TimerStart(&fpsTimer); /* To calculate FPS */

    int32_t frameCount;
    float fpsAverage = 0.0f;
    float deltaTime = 0.0f;

    DeccanSettings *settings = DE_CoreGetSettings();

    DE_SceneMakeChanges();

    while (DE_CoreIsRunning()) {
        DE_TimerStart(&frmTimer);

        /* Calculate FPS */
        fpsAverage = frameCount / DE_TimerGetTime(&fpsTimer).seconds;
        if (fpsAverage > 20000) {
            fpsAverage = 0.0f;
        }

        DE_CoreUpdate(fpsAverage, deltaTime);

        vec2s viewport;
        DE_CoreGetResolution(viewport.raw);
        DE_RendererSetViewport(viewport);

        /* Update and render the scene */
        DE_GenericPipelineBegin(DE_SceneGetCamera());
        DE_SceneUpdate();
        DE_GenericPipelineEnd();

        /* Render everything */
        DE_RendererDraw();

        /* Increment the frame counter */
        frameCount++;

        /* Current ticks per frame i.e delta time */
        deltaTime = DE_TimerGetTime(&frmTimer).milliseconds;

        /* Limit FPS */
        if ((!settings->vsync) && (settings->fps > 20.0f)) {
            float ticksPerFrame = (1000.0f / settings->fps); /* Required ticks per frame */
            if (deltaTime < ticksPerFrame) {
                DE_ClockDelay((int)(ticksPerFrame - deltaTime));
            }
        }

        /* Update delta time */
        deltaTime = DE_TimerGetTime(&frmTimer).milliseconds;
    }
}

void DE_AppQuit(void) {
    DE_SceneQuit();

    DE_SceneFreeAll();

    DE_GenericPipelineDestroy();
    DE_RendererDestroy();

    DE_CoreQuit();
}
