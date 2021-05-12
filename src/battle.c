#include "simple_logger.h"
#include "gf2d_audio.h"

#include "battle.h"
#include "camera.h"
#include "shape.h"

Uint16 type, battle, select;
Uint16 atk2, atk3, atk4;
const Uint8 *keys;
const char *enemytype;
int playerhp, enemyhp;
Uint16 level = 1;
Uint16 stun, flaming, sleeping;
const char *second = "nothing", *third = "nothing", *fourth = "nothing";
float wait, wait2;
int eturn;
int experience = 0;
int r1;
Mix_Music *bmusic;

void battle_initiate(Uint16 enemy)
{
	battlestart();
	type = enemy;
	battle = 1;
	select = 1;
	wait = 10;
	wait2 = 10;
	playerhp = 80 + 20 * level;
	eturn = 0;
	stun = 0;
	sleeping = 0;
	flaming = 0;
	r1 = 1;
	bmusic = Mix_LoadMUS("music/battlemusic.mp3");
	switch (type)
	{
	case 1:
		enemytype = "Stinkman";
		enemyhp = 75;
		break;
	case 2:
		enemytype = "Waterman";
		enemyhp = 100;
		break;
	case 3:
		enemytype = "Fireman";
		enemyhp = 200;
		break;
	case 4:
		enemytype = "Magicman";
		enemyhp = 300;
		break;
	case 5:
		enemytype = "Antihero";
		enemyhp = 500;
		break;
	}
	slog("%s appears!", enemytype);
}
void battlethink(Entity *self)
{
	if (wait > 0)
	{
		wait -= 0.1;
	}
	
	if (battle == 1)
	{
		if (enemyhp <= 0)
		{
			battleend();
			switch (type)
			{
				case 1:
					experience += 50;
					break;
				case 2:
					experience += 100;
					break;
				case 3:
					experience += 150;
					break;
				case 4:
					experience += 200;
					break;
				case 5:
					experience += 250;
					break;
			}
			level = 1 + experience / 100;
			slog("You are level %d!", level);
		}
		switch (type)
		{
		case 1:
			self->sprite = gf2d_sprite_load_all("images/stinkman.png", 256, 256, 16);
			self->position = vector2d(camera_get_position().x + 472, camera_get_position().y + 100);
			break;
		case 2:
			self->sprite = gf2d_sprite_load_all("images/waterman.png", 256, 256, 16);
			self->position = vector2d(camera_get_position().x + 472, camera_get_position().y + 100);
			break;
		case 3:
			self->sprite = gf2d_sprite_load_all("images/fireman.png", 256, 256, 16);
			self->position = vector2d(camera_get_position().x + 472, camera_get_position().y + 100);
			break;
		case 4:
			self->sprite = gf2d_sprite_load_all("images/magicman.png", 256, 256, 16);
			self->position = vector2d(camera_get_position().x + 472, camera_get_position().y + 100);
			break;
		case 5:
			self->sprite = gf2d_sprite_load_all("images/antihero.png", 512, 512, 16);
			self->position = vector2d(camera_get_position().x + 344, camera_get_position().y + 100);
			break;
		}
		if (keys[SDL_SCANCODE_SPACE] && wait <= 0 && eturn == 0)
		{
			wait = 10;
			switch (select)
			{
				case 1:
					slog("You used %s!", "punch");
					bpunch();
					break;
				case 2:
					slog("You used %s!", second);
					attack(atk2);
					break;
				case 4:								//These two swap for some reason and I have zero idea why, it doesn't work right unless they're switched
					slog("You used %s!", third);
					attack(atk3);
					break;
				case 3:								//^^^
					slog("You used %s!", fourth);
					attack(atk4);
					break;
			}
			eturn = 1;
		}
		if (eturn == 1)
		{
			if (wait2 > 0)
			{
				wait2 -= 0.1;
			}
			if (wait2 <= 0)
			{
				if (r1 == 1)
				{
					r1 = 0;
					Mix_PlayMusic(bmusic, -1);
				}
				enemyturn();
			}
			if (wait2 <= 0)
			{
				wait2 = 10;
				slog("Player HP: %d -------------- Enemy HP: %d", playerhp, enemyhp);
				eturn = 0;
				if (playerhp <= 0)
				{
					slog("You're out of HP, you lose! Try playing again? Or you can keep going, but that's cheating!");
				}
			}
		}
	}
	else
	{
		self->position = vector2d(-2000, -2000);
	}

}
void enemyturn()
{
	int damage;
	if (stun > 0)
	{
		slog("%s is stunned!", enemytype);
		estunned();
	}
	else if (sleeping > 0)
	{
		slog("%s is asleep!", enemytype);
		esleeping();
	}
	else
	{
		switch (type)
		{
		case 1:
			if (gfc_random() * 100 < 20)
			{
				slog("%s missed!", enemytype);
			}
			else
			{
				damage = (gfc_random() / 5) * 100 + 10 + (gfc_random() * 5);
				slog("%s's attack dealt %d damage to you!", enemytype, damage);
				playerhp -= damage;
			}
			break;
		case 2:
			if (gfc_random() * 100 < 20)
			{
				slog("%s missed!", enemytype);
			}
			else
			{
				damage = (gfc_random() / 5) * 100 + 10 + (gfc_random() * 15);
				slog("%s's attack dealt %d damage to you!", enemytype, damage);
				playerhp -= damage;
			}
			break;
		case 3:
			if (gfc_random() * 100 < 20)
			{
				slog("%s missed!", enemytype);
			}
			else
			{
				damage = (gfc_random() / 4) * 100 + 10 + (gfc_random() * 10);
				slog("%s's attack dealt %d damage to you!", enemytype, damage);
				playerhp -= damage;
			}
			break;
		case 4:
			if (gfc_random() * 100 < 20)
			{
				slog("%s missed!", enemytype);
			}
			else
			{
				damage = (gfc_random() / 3) * 100 + 10 + (gfc_random() * 5);
				slog("%s's attack dealt %d damage to you!", enemytype, damage);
				playerhp -= damage;
			}
			break;
		case 5:
			if (gfc_random() * 100 < 20)
			{
				slog("%s missed!", enemytype);
			}
			else
			{
				damage = (gfc_random() / 2) * 100 + 10 + (gfc_random() * 25);
				slog("%s's attack dealt %d damage to you!", enemytype, damage);
				playerhp -= damage;
			}
			break;
		}
	}
	eflaming();
}
void bselect(Entity *self)
{
	if (battle == 1)
	{
		self->sprite = gf2d_sprite_load_all("images/highlight.png", 311, 166, 16);
		if (keys[SDL_SCANCODE_W] && select > 2)
		{
			select -= 2;
		}
		if (keys[SDL_SCANCODE_A] && select != 1 && select != 3)
		{
			select -= 1;
		}
		if (keys[SDL_SCANCODE_S] && select < 3)
		{
			select += 2;
		}
		if (keys[SDL_SCANCODE_D] && select != 2 && select != 4)
		{
			select += 1;
		}
		switch (select)
		{
		case 1:
			self->position = vector2d(camera_get_position().x + 50, camera_get_position().y + 75);
			break;
		case 2:
			self->position = vector2d(camera_get_position().x + 850, camera_get_position().y + 75);
			break;
		case 3:
			self->position = vector2d(camera_get_position().x + 50, camera_get_position().y + 495);
			break;
		case 4:
			self->position = vector2d(camera_get_position().x + 850, camera_get_position().y + 495);
			break;
		}

	}
	else
	{
		self->position = vector2d(-2000, -2000);
	}

}
void ba1(Entity *self)
{
	if (battle == 1)
	{
		self->sprite = gf2d_sprite_load_all("images/words/punch.png", 181, 46, 16);
		self->position = vector2d(camera_get_position().x + 80, camera_get_position().y + 125);
	}
	else
	{
		self->position = vector2d(-2000, -2000);
	}
}
void ba2(Entity *self)
{
	if (battle == 1)
	{
		atk2 = B2();
		switch (atk2)
		{
			case 1:
				self->sprite = gf2d_sprite_load_all("images/words/smite.png", 186, 51, 16);
				self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 125);
				second = "smite";
				break;
			case 2:
				self->sprite = gf2d_sprite_load_all("images/words/lullaby.png", 255, 61, 16);
				self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 125);
				second = "lullaby";
				break;
			case 3:
				self->sprite = gf2d_sprite_load_all("images/words/storm.png", 185, 46, 16);
				self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 125);
				second = "storm";
				break;
			case 4:
				self->sprite = gf2d_sprite_load_all("images/words/bash.png", 144, 46, 16);
				self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 125);
				second = "bash";
				break;
			case 5:
				self->sprite = gf2d_sprite_load_all("images/words/dance.png", 180, 46, 16);
				self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 125);
				second = "dance";
				break;
			case 6:
				self->sprite = gf2d_sprite_load_all("images/words/fireball.png", 292, 51, 16);
				self->position = vector2d(camera_get_position().x + 860, camera_get_position().y + 125);
				second = "fireball";
				break;
			case 7:
				self->sprite = gf2d_sprite_load_all("images/words/slash.png", 181, 46, 16);
				self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 125);
				second = "slash";
				break;
			case 8:
				self->sprite = gf2d_sprite_load_all("images/words/whistle.png", 260, 51, 16);
				self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 125);
				second = "whistle";
				break;
			case 9:
				self->sprite = gf2d_sprite_load_all("images/words/mm.png", 260, 136, 16);
				self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 85);
				second = "magic missile";
				break;
		}
	}
	else
	{
		self->position = vector2d(-2000, -2000);
	}
}
void ba3(Entity *self)
{
	if (battle == 1)
	{
		atk3 = B3();
		switch (atk3)
		{
		case 1:
			self->sprite = gf2d_sprite_load_all("images/words/smite.png", 186, 51, 16);
			self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 550);
			third = "smite";
			break;
		case 2:
			self->sprite = gf2d_sprite_load_all("images/words/lullaby.png", 255, 61, 16);
			self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 550);
			third = "lullaby";
			break;
		case 3:
			self->sprite = gf2d_sprite_load_all("images/words/storm.png", 185, 46, 16);
			self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 550);
			third = "storm";
			break;
		case 4:
			self->sprite = gf2d_sprite_load_all("images/words/bash.png", 144, 46, 16);
			self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 550);
			third = "bash";
			break;
		case 5:
			self->sprite = gf2d_sprite_load_all("images/words/dance.png", 180, 46, 16);
			self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 550);
			third = "dance";
			break;
		case 6:
			self->sprite = gf2d_sprite_load_all("images/words/fireball.png", 292, 51, 16);
			self->position = vector2d(camera_get_position().x + 860, camera_get_position().y + 550);
			third = "fireball";
			break;
		case 7:
			self->sprite = gf2d_sprite_load_all("images/words/slash.png", 181, 46, 16);
			self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 550);
			third = "slash";
			break;
		case 8:
			self->sprite = gf2d_sprite_load_all("images/words/whistle.png", 260, 51, 16);
			self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 550);
			third = "whistle";
			break;
		case 9:
			self->sprite = gf2d_sprite_load_all("images/words/mm.png", 260, 136, 16);
			self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 500);
			third = "magic missile";
			break;
		}
	}
	else
	{
		self->position = vector2d(-2000, -2000);
	}
}
void ba4(Entity *self)
{
	if (battle == 1)
	{
		atk4 = B4();
		switch (atk4)
		{
		case 1:
			self->sprite = gf2d_sprite_load_all("images/words/smite.png", 186, 51, 16);
			self->position = vector2d(camera_get_position().x + 80, camera_get_position().y + 550);
			fourth = "smite";
			break;
		case 2:
			self->sprite = gf2d_sprite_load_all("images/words/lullaby.png", 255, 61, 16);
			self->position = vector2d(camera_get_position().x + 80, camera_get_position().y + 550);
			fourth = "lullaby";
			break;
		case 3:
			self->sprite = gf2d_sprite_load_all("images/words/storm.png", 185, 46, 16);
			self->position = vector2d(camera_get_position().x + 80, camera_get_position().y + 550);
			fourth = "storm";
			break;
		case 4:
			self->sprite = gf2d_sprite_load_all("images/words/bash.png", 144, 46, 16);
			self->position = vector2d(camera_get_position().x + 80, camera_get_position().y + 550);
			fourth = "bash";
			break;
		case 5:
			self->sprite = gf2d_sprite_load_all("images/words/dance.png", 180, 46, 16);
			self->position = vector2d(camera_get_position().x + 80, camera_get_position().y + 550);
			fourth = "dance";
			break;
		case 6:
			self->sprite = gf2d_sprite_load_all("images/words/fireball.png", 292, 51, 16);
			self->position = vector2d(camera_get_position().x + 60, camera_get_position().y + 550);
			fourth = "fireball";
			break;
		case 7:
			self->sprite = gf2d_sprite_load_all("images/words/slash.png", 181, 46, 16);
			self->position = vector2d(camera_get_position().x + 80, camera_get_position().y + 550);
			fourth = "slash";
			break;
		case 8:
			self->sprite = gf2d_sprite_load_all("images/words/whistle.png", 260, 51, 16);
			self->position = vector2d(camera_get_position().x + 80, camera_get_position().y + 550);
			fourth = "whistle";
			break;
		case 9:
			self->sprite = gf2d_sprite_load_all("images/words/mm.png", 260, 136, 16);
			self->position = vector2d(camera_get_position().x + 100, camera_get_position().y + 500);
			fourth = "magic missile";
			break;
		}
	}
	else
	{
		self->position = vector2d(-2000, -2000);
	}
}
void attack(Uint16 type)
{
	switch (type)
	{
		case 1:
			bsmite();
			break;
		case 2:
			blullaby();
			break;
		case 3:
			bstorm();
			break;
		case 4:
			bbash();
			break;
		case 5:
			bdance();
			break;
		case 6:
			bfireball();
			break;
		case 7:
			bslash();
			break;
		case 8:
			bwhistle();
			break;
		case 9:
			bmm();
			break;
	}
}
void bpunch()
{
	int damage;
	if (gfc_random() * 100 < 15)
	{
		slog("Your punch missed!");
	}
	else
	{
		damage = (gfc_random() / 5) * 100 + 10 + (gfc_random() * 5 * level);
		slog("Your punch dealt %d damage to %s!", damage, enemytype);
		enemyhp -= damage;
	}
}
void bsmite()
{
	int damage;
	damage = (gfc_random() * 30) * level;
	slog("Your smite dealt %d damage to %s!", damage, enemytype);
	enemyhp -= damage;
}
void blullaby()
{
	int turns;
	if (gfc_random() * 100 < 75 - 5 * level)
	{
		slog("Your lullaby failed!");
	}
	else
	{
		sleeping = 1;
		slog("Your lullaby put the %s to sleep!", enemytype);
	}
}
void bstorm()
{
	int damage;
	damage = (gfc_random() * 20) * level + 10;
	slog("Your storm dealt %d damage to %s!", damage, enemytype);
	enemyhp -= damage;
}
void bbash()
{
	int damage;
	int turns;
	if (gfc_random() * 100 < 45 - 5 * level)
	{
		slog("Your bash failed!");
	}
	else
	{
		turns = (gfc_random() / 33) * 100 + level;
		damage = (gfc_random() / 5) * 100 + (gfc_random() * 5 * level);
		stun += turns;
		if (turns > 1)
			slog("Your bash stunned the %s for %d turns, dealing %d damage!", enemytype, stun, damage);
		else
			slog("Your bash stunned the %s for %d turn, dealing %d damage!", enemytype, stun, damage);
	}
}
void bdance()
{
	if (gfc_random() * 100 < 90)
	{
		slog("You danced, nothing happened!");
	}
	else
	{
		slog("You danced so hard that %s exploded!", enemytype);
		enemyhp = 0;
	}
}
void bfireball()
{
	int damage;
	int turns;
	turns = (gfc_random() / 25) * 100 + level;
	flaming += turns;
	damage = (gfc_random() / 5) * 100 + (gfc_random() * 10 * level);
	if (flaming > 1)
		slog("Your fireball dealt %d damage to %s, setting them on fire for %d turns!", damage, enemytype, flaming);
	else
		slog("Your fireball dealt %d damage to %s, setting them on fire for %d turn!", damage, enemytype, flaming);
	enemyhp -= damage;
}
void bslash()
{
	int damage;
	if (gfc_random() * 100 < 20)
	{
		slog("Your slash missed!");
	}
	else
	{
		damage = (gfc_random() / 3) * 100 + 10 + (gfc_random() * 10 * level);
		slog("Your slash dealt %d damage to %s!", damage, enemytype);
		enemyhp -= damage;
	}
}
void bwhistle()
{
	int turns;
	if (gfc_random() * 100 < 55 - 5 * level)
	{
		slog("Your whistle failed!");
	}
	else
	{
		turns = (gfc_random() / 25) * 100 + level;
		stun += turns;
		slog("Your whistle stunned the %s for %d turns!", enemytype, stun);
	}
}
void bmm()
{
	int damage;
	damage = (gfc_random() / 5) * 100 + (gfc_random() * 10 * level);
	slog("Your magic missile dealt %d damage to %s!", damage, enemytype);
	enemyhp -= damage;
}
void estunned()
{
	if (stun > 0)
	{
		stun -= 1;
	}
}
void eflaming()
{
	if (flaming > 0)
	{
		flaming -= 1;
		int damage;
		damage = (gfc_random() / 10) * 100 + (gfc_random() / 20) * 100 * level;
		slog("%s took %d damage due to fire!", enemytype, damage);
		enemyhp -= damage;
	}
}
void esleeping()
{
	if (sleeping > 0)
	{
		if (gfc_random() * 100 < 10)
		{
			slog("%s woke up!", enemytype);
			sleeping = 0;
		}
	}
}
/**/