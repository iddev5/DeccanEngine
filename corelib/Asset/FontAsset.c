/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "FontAsset.h"

#define PTR_NULLCHECK(x,y) if(!x) { return y; }

/////////////////////////////////////////////////
// Constructor/Destructor
////////////////////////////////////////////////

FontAsset *Font_New(const char *name) {
    FontAsset *asset = DE_Mem_New(sizeof(FontAsset), 1);
    asset->name = DE_String_New(name);
    return asset;
}

void Font_Delete(FontAsset *asset) {
	if(!asset) return;

    DE_Mem_Delete(asset->name);
    DE_Mem_Delete(asset->font);
    DE_Mem_Delete(asset);
}

/////////////////////////////////////////////////
// Setters/Getters
////////////////////////////////////////////////

void Font_SetKerning(FontAsset *font, bool kerning) {
    PTR_NULLCHECK(font,);

    TTF_SetFontKerning(font->font, kerning ? 1 : 0);
}

bool Font_GetKerning(FontAsset *font) {
    PTR_NULLCHECK(font, false);

    return (bool)TTF_GetFontKerning(font->font);
}

/////////////////////////////////////////////////
// Utility functions
////////////////////////////////////////////////

void Font_CalculateTextSize(FontAsset *font, const char *text, vec2 size) {
    int32_t x = -1;
    int32_t y = -1;
    size[0] = -1;
    size[1] = -1;

    PTR_NULLCHECK(font,);
    TTF_SizeText(font->font, text, &x, &y);

    size[0] = (float)x;
    size[1] = (float)y;
}

#undef PTR_NULLCHECK
