/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../depends/stb_ds.h"

/* Define basic constants */
#ifndef PI 
    #define PI 3.14159265358979323846
#endif

#define DEG2RAD (PI/180.0000)
#define RAD2DEG (180.0000/PI)

/* Texture structure depends on backend */
#ifdef DECCAN_RENDERER_SDL
    typedef SDL_Texture RawTexture;
#endif

/* Memory management functions */
#ifndef DE_NEW
    #define DE_NEW(type,size) (type*)malloc(sizeof(type)*size);
#endif

static inline char *DE_NEWSTRING(const char *source) {
    char *string = DE_NEW(char, strlen(source));
    strcpy(string, source);
    return string;
}

/* Error handling/logging */
extern void DE_ERROR (const char *str, ...);
extern void DE_REPORT(const char *str, ...);