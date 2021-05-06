/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "../Components/DrawableSprite.h"
#include "../Flecs.h"
#include "../../Renderer/RenderTypes.h"
#include "../../Renderer/GenericPipeline.h"
#include "../Components/Transform.h"
#include "../Components/DrawableGeometry.h"
#include "../Components/DrawableSprite.h"

////////////////////////////////////////////////////////////////////////////////
// Rendering systems
////////////////////////////////////////////////////////////////////////////////

DE_PRIV void WorldSpriteRendering(deccan_flecs_iter_t *it) {
    deccan_comp_transform_t *transform = deccan_flecs_iter_column(it, "Transform", 1);
    deccan_comp_drawable_sprite_t *sprrender = deccan_flecs_iter_column(it, "DrawableSprite", 2);

    for (int i = 0; i < it->count; i++) {
        mat4s transmat = glms_mat4_identity();
        glm_translate(transmat.raw, transform->position);
        glm_scale(transmat.raw, transform->scale);

        deccan_geometry_t quad = deccan_primitive_create_quad();

        deccan_draw_action_t action;
        action.geometry = &quad;
        action.transform = transmat;
        action.material = &sprrender[i].material;
        action.texture = sprrender[i].texture;
        
        deccan_generic_pipeline_draw(action);
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_PRIV void WorldArbitaryGeometryRendering(deccan_flecs_iter_t *it) {
    deccan_comp_transform_t *transform = deccan_flecs_iter_column(it, "Transform", 1);
    deccan_comp_drawable_geometry_t *arbrender = deccan_flecs_iter_column(it, "DrawableGeometry", 2);

    for (int i = 0; i < it->count; i++) {
        mat4s transmat = glms_mat4_identity();
        glm_translate(transmat.raw, transform->position);
        glm_scale(transmat.raw, transform->scale);

        deccan_draw_action_t action;
        action.geometry = &arbrender[i].geometry;
        action.transform = transmat;
        action.material = &arbrender[i].material;
        action.texture = arbrender[i].texture;
        
        deccan_generic_pipeline_draw(action);
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_system_init_rendering(void) {
    deccan_flecs_system(WorldSpriteRendering, "DrawableSpriteRendering", "Transform, DrawableSprite", DECCAN_ECS_TYPE_ON_UPDATE);

    deccan_flecs_system(WorldArbitaryGeometryRendering, "DrawableGeometryRendering", "Transform, DrawableGeometry", DECCAN_ECS_TYPE_ON_UPDATE);
}