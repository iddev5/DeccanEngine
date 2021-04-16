/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Color.h"

/////////////////////////////////////////////////
// Color conversions
////////////////////////////////////////////////

DE_API DeccanColor DE_ColorRBGToFloats(DeccanColor col) {
    DeccanColor out;
    out.norm[0] = (float)(col.r) / 255.0f;
    out.norm[1] = (float)(col.g) / 255.0f;
    out.norm[2] = (float)(col.b) / 255.0f;
    out.norm[3] = (float)(col.a) / 255.0f;
    return out;
}

DE_API DeccanColor DE_ColorFloatsToRBG(DeccanColor col) {
    DeccanColor out;
    out.r = (int8_t)(col.norm[0] * 255.0f);
    out.g = (int8_t)(col.norm[1] * 255.0f);
    out.b = (int8_t)(col.norm[2] * 255.0f);
    out.a = (int8_t)(col.norm[3] * 255.0f);
    return out;
}
