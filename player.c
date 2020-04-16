#include "player.h"

void _player_begin(GameObject *this) {
    this->x = 100;
    this->y = 100;
}

void _player_step(GameObject *this) {
    if(Input.key_held(Key.w)){ this->y-=1; }
    else if(Input.key_held(Key.s)){ this->y+=1; }
    else if(Input.key_held(Key.a)){ this->x-=1; }
    else if(Input.key_held(Key.d)){ this->x+=1; }
    
    Color col;
    Vector2i pos = Input.get_mouse_pos();
    if(pos.x > this->x && pos.x < this->x+50 && pos.y > this->y && pos.y < this->y+50) {
        if(Input.button_down(Button.left)) {
            col = ColorList.green;
        }
        else { col = ColorList.dark_green; }
    }
    else {
        col = ColorList.black;
    }

    Renderer.draw_rect((Rect){this->x, this->y, 50, 50}, true, col);
    Renderer.draw_circle((Vector3i){this->x+100, this->y+100, 50}, true, col);
    Renderer.draw_scaled_texture((Vector2i){this->x+200, this->y+200}, (Vector2f){2.0f, 2.0f}, Asset.get_texture("arrow"));
}

void _player_end(GameObject *this) { }