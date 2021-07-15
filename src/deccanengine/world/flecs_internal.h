/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include <deccanengine/config.h>

////////////////////////////////////////////////////////////////////////////////
// World
////////////////////////////////////////////////////////////////////////////////

void flecs_update_world(void);

////////////////////////////////////////////////////////////////////////////////
// Component
////////////////////////////////////////////////////////////////////////////////

void flecs_set_component(ecs_entity_t entity, const char *name, void *component);
void *flecs_get_component(ecs_entity_t entity, const char *name);
void flecs_remove_component(ecs_entity_t entity, const char *name);

////////////////////////////////////////////////////////////////////////////////
// Tag
////////////////////////////////////////////////////////////////////////////////

void flecs_set_tag(ecs_entity_t entity, const char *name);
bool flecs_has_tag(ecs_entity_t entity, const char *name);