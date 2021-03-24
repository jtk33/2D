#ifndef __BATTLE_H__
#define __BATTLE_H__

#include "entity.h"
#include "player.h"

void battle_initiate(Uint16 enemy);
void battlethink(Entity *self);
void bselect(Entity *self);
void ba1(Entity *self);
void ba2(Entity *self);
void ba3(Entity *self);
void ba4(Entity *self);

#endif