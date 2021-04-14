/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "PrimitiveGeometry.h"
#include "RenderTypes.h"
#include "../World/Camera.h"

/////////////////////////////////////////////////
// Pipeline constructor/destructor
////////////////////////////////////////////////

DE_API void DE_GenericPipelineCreate(void);
DE_API void DE_GenericPipelineDestroy(void);

/////////////////////////////////////////////////
// Pipeline action
////////////////////////////////////////////////

DE_API void DE_GenericPipelineBegin(DeccanCamera *camera);
DE_API void DE_GenericPipelineDraw(DeccanDrawAction action);
DE_API void DE_GenericPipelineEnd(void);
