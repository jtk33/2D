#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "entity.h"

/**
* @brief spawn a player entity
* @param position the screen position to spawn the player at
* @return NULL on error, or a pointer to a new player entity
*/
Entity *player_spawn(Vector2D position);
void menuthink(Entity *self);
void backgroundthink(Entity *self);
void selectthink(Entity *self);
ShapeRect hitbox();
void change(Uint16 type);
void battlestart();
void battleend();
Uint16 B2();
Uint16 B3();
Uint16 B4();
#endif