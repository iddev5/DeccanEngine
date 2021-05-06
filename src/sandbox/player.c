#include "player.h"

bool selected = false;
vec2 offset;

deccan_color_t ColorList_White = (deccan_color_t){255, 255, 255, 255}, ColorList_Black = (deccan_color_t){0, 0, 0, 255},
            ColorList_Red = (deccan_color_t){255, 0, 0, 255}, ColorList_Green = (deccan_color_t){0, 255, 0, 255},
            ColorList_Orange = (deccan_color_t){255, 165, 0, 255};

void _player_begin(deccan_game_object_t this) {
    deccan_object_info_t *info = deccan_object_get_component(this, "Info");

    deccan_object_set_component(this, "Collider", &(deccan_comp_collider_t){
        .type = DECCAN_COLLIDER_RECT, 
        .rect = { [0] = 0, [1] = 0, [2] = 50, [3] = 50 }
    });

    deccan_object_set_component(this, "Transform", &(deccan_comp_transform_t){
        .position = { [0] = 1.0f, [1] = 0.0f, [2] = 0.0f },
        .scale = { [0] = 5.0f, [1] = 5.0f, [2] = 1.0f }
    });

    deccan_object_set_component(this, "DrawableSprite", &(deccan_comp_drawable_sprite_t){
        .texture = deccan_asset_get_raw(deccan_asset_get("texture", "logo.png")),
        .material = (deccan_material_t){
            .color = (deccan_color_t){ 255, 255, 255, 255 },
        },
    });
}

void _player_step(deccan_game_object_t this) {
    static float SpeedModifier = 2e-2f;
    deccan_comp_transform_t *state = deccan_object_get_component(this, "Transform");

    if (deccan_input_key_held(DECCAN_KEY_W)) {
        state->position[1] += SpeedModifier;
    }
    else if (deccan_input_key_held(DECCAN_KEY_S)) {
        state->position[1] -= SpeedModifier;
    }
    else if (deccan_input_key_held(DECCAN_KEY_A)) {
        state->position[0] -= SpeedModifier;
    }
    else if (deccan_input_key_held(DECCAN_KEY_D)) {
        state->position[0] += SpeedModifier;
    }

    if (deccan_input_key_released(DECCAN_KEY_O)) {
        SpeedModifier -= 1;
    }
    else if (deccan_input_key_released(DECCAN_KEY_P)) {
        SpeedModifier += 1;
    }

    /* Center the camera on player */
    // Camera_CenterOn(this);

    vec2 pos;
    deccan_input_get_mouse_pos(pos);
    if (deccan_comp_collider_check_object_with_vector(this, pos)) {
        // *color = ColorList_Orange;
        if (deccan_input_button_down(DECCAN_BUTTON_LEFT)) {
            selected = true;
            offset[0] = pos[0] - state->position[0];
            offset[1] = pos[1] - state->position[1];
        }
        else if (deccan_input_button_up(DECCAN_BUTTON_LEFT)) {
            selected = false;
        }
    }

    if (selected) {
        state->position[0] = pos[0] - offset[0];
        state->position[1] = pos[1] - offset[1];
    }
}

void _player_render(deccan_game_object_t this) {
    deccan_comp_transform_t *state = deccan_object_get_component(this, "Transform");

    igBegin("Transform", NULL, 0);
    igDragFloat("X", &state->position[0], 0.1f, 0.0f, 0.0f, "%.2f", 0);
    igDragFloat("Y", &state->position[1], 0.1f, 0.0f, 0.0f, "%.2f", 0);
    igDragFloat("Z", &state->position[2], 0.1f, 0.0f, 0.0f, "%.2f", 0);
    igEnd();
}

void _player_end(deccan_game_object_t this) {
    DE_UNUSED(this);
}

void _none_begin(deccan_game_object_t this) {
    deccan_game_object_t player = deccan_scene_get_object("main player");
    deccan_comp_transform_t *statePlayer = deccan_object_get_component(player, "Transform");

    deccan_object_set_component(this, "Transform", &(deccan_comp_transform_t){
        .position = { [0] = statePlayer->position[0], [1] = statePlayer->position[1] }
    });
    deccan_object_set_component(this, "Collider", &(deccan_comp_collider_t){
        .type = DECCAN_COLLIDER_RECT, 
        .rect = {[0] = 0, [1] = 0, [2] = 40, [3] = 40}
    });
    deccan_object_set_tag(this, "isEnemy");
}

void _none_step(deccan_game_object_t this) {
    DE_UNUSED(this);
}

void _none_render(deccan_game_object_t this) {
    deccan_comp_transform_t *state = deccan_object_get_component(this, "Transform");
}

void _none_end(deccan_game_object_t this) {
    DE_UNUSED(this);
}