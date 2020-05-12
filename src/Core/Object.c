/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Object.h>
#include <Deccan/Scene.h>
#include <Deccan/Core.h>

void _msg_send(GameObject *obj, const char *msg) {
    Msg_Send(&obj->msg, msg);
}

bool _msg_receive(GameObject *obj, const char *msg) {
    return Msg_Receive(&obj->msg, msg);
}

#define obj_func(x) void (*x)(GameObject *object)

GameObject *Object_NewObject(
    const char *name, const char *type, 
    obj_func(af), obj_func(ab), obj_func(as), obj_func(ar), obj_func(ae)) {
    
    GameObject *obj = DE_NEW(GameObject, 1);
    
    obj->info.name = DE_NEWSTRING(name);
    obj->info.type = DE_NEWSTRING(type);
    
    obj->angle = 0.0f;
    
    Msg_Init(&obj->msg, DECCAN_OBJ_MSG_COUNT, DECCAN_OBJ_MSG_LENGTH);
    obj->SendMessage = _msg_send;
    obj->ReceiveMessage = _msg_receive;
    
    obj->is_beginning = true;
    obj->AtFirstFrame = af;
    obj->AtBeginning = ab;
    obj->AtStep = as;
    obj->AtRender = ar;
    obj->AtEnd = ae;

    return obj;
}

#undef obj_func

#define PTR_NULLCHECK(x) if(x == NULL) { return; }  

void Object_InstantiateObject(GameObject *object) {
    PTR_NULLCHECK(object);
    
    GameScene *scene = Scene_CurrentScene(); 
    if(stbds_arrput(scene->objects, object) != object) {
        DE_REPORT("Cannot instantiate object: %s", object->info.name); return;
    }
    scene->object_count++;
}

GameObject *Object_GetObject(const char *name) {
    GameScene *scene = Scene_CurrentScene();
    for(int i=0; i<scene->object_count; i++) {
        if(!strcmp(scene->objects[i]->info.name, name)) {
            return scene->objects[i];
        }
    }
    DE_REPORT("GameObject not found: %s", name);
}

void Object_GetObjectOfType(const char *name, void(*func)(GameObject *obj)) {
    GameScene *scene = Scene_CurrentScene();
    for(int i=0; i<scene->object_count; i++) {
        if(!strcmp(scene->objects[i]->info.type, name)) {
            func(scene->objects[i]);
        }
    }
}

void _clamp_angle(double *angle) {
    while(*angle > 360) { *angle -= 360; }
    while(*angle <   0) { *angle += 360; }
}

/* Setters */

void Object_SetAngle(GameObject *obj, double angle) {
    PTR_NULLCHECK(obj);
    
    _clamp_angle(&angle);
    obj->angle = angle;
}

/* Getters */

double Object_GetAngle(GameObject *obj) {
    PTR_NULLCHECK(obj);
    
    _clamp_angle(&obj->angle);
    return obj->angle;
}

/* Object rotation functions */

int _angle_diff(double a1, double a2) {
    return ((((int)(a1 - a2) % 360) + 180) % 360) - 180;
}

/* WIP */
void Object_Rotate(GameObject *obj, double angle, int speed) {
    PTR_NULLCHECK(obj);

    if(speed <= 0) { 
        obj->angle = angle; 
        return;
    }

    _clamp_angle(&obj->angle);
    _clamp_angle(&angle);

    //double doaa = 180.0f - abs(abs(obj->angle - angle) - 180.0f);
    int doaa = _angle_diff(obj->angle, angle);
    
    if(doaa == 0 || doaa == (speed * -1)) { return; }
    else {
        bool is_positive = (doaa >= 0);
        double new_angle = obj->angle + ((is_positive ? -1.0f : 1.0f) * (speed)); //* (Core_GetDeltaTime()));
    
        //double dnaa = 180.0f - abs(abs(new_angle - angle) - 180.0f);
        int dnaa = _angle_diff(new_angle, angle);
        //printf("angle_diff = %d is_positive = %d\n", dnaa, is_positive);

        if((dnaa >= 0) ^ is_positive) {
            new_angle = angle;
        }
        
        obj->angle = new_angle;
    }
}

void Object_RotateTowardsObject(GameObject *obj, GameObject *target, int speed) {
    PTR_NULLCHECK(target);
    Object_RotateTowardsPosition(obj, target->position, speed);
}

void Object_RotateTowardsPosition(GameObject *obj, Vector2f pos, int speed) {
    PTR_NULLCHECK(obj);

    double angle;
    angle = atan2(pos.y - obj->position.y, pos.x - obj->position.x);
    angle = angle * 180.0000 / 3.14159;

    obj->angle = angle;
    // Object_Rotate(obj, angle, speed);
}

#undef PTR_NULLCHECK