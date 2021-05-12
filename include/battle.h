#ifndef __BATTLE_H__
#define __BATTLE_H__

#include "entity.h"
#include "player.h"

void battle_initiate(Uint16 enemy);
void battlethink(Entity *self);
void enemyturn();
void bselect(Entity *self);
void ba1(Entity *self);
void ba2(Entity *self);
void ba3(Entity *self);
void ba4(Entity *self);
void attack(Uint16 type);
void bpunch(); 
void bsmite();
void blullaby();
void bstorm();
void bbash();
void bdance();
void bfireball();
void bslash();
void bwhistle();
void bmm();
void estunned();
void eflaming();
void esleeping();
#endif