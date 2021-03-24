#include "simple_logger.h"

#include "battle.h"
#include "camera.h"
#include "shape.h"

Uint16 type, battle, select;
Uint16 atk2, atk3, atk4;
const Uint8 *keys;

void battle_initiate(Uint16 enemy)
{
	battlestart();
	type = enemy;
	battle = 1;
	select = 1;
}
void battlethink(Entity *self)
{
	if (battle == 1)
	{
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
	}

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

}
void ba1(Entity *self)
{
	if (battle == 1)
	{
		self->sprite = gf2d_sprite_load_all("images/words/punch.png", 181, 46, 16);
		self->position = vector2d(camera_get_position().x + 80, camera_get_position().y + 125);
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
				break;
			case 2:
				self->sprite = gf2d_sprite_load_all("images/words/lullaby.png", 255, 61, 16);
				self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 125);
				break;
			case 3:
				self->sprite = gf2d_sprite_load_all("images/words/storm.png", 185, 46, 16);
				self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 125);
				break;
			case 4:
				self->sprite = gf2d_sprite_load_all("images/words/bash.png", 144, 46, 16);
				self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 125);
				break;
			case 5:
				self->sprite = gf2d_sprite_load_all("images/words/dance.png", 180, 46, 16);
				self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 125);
				break;
			case 6:
				self->sprite = gf2d_sprite_load_all("images/words/fireball.png", 292, 51, 16);
				self->position = vector2d(camera_get_position().x + 860, camera_get_position().y + 125);
				break;
			case 7:
				self->sprite = gf2d_sprite_load_all("images/words/slash.png", 181, 46, 16);
				self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 125);
				break;
			case 8:
				self->sprite = gf2d_sprite_load_all("images/words/whistle.png", 260, 51, 16);
				self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 125);
				break;
			case 9:
				self->sprite = gf2d_sprite_load_all("images/words/mm.png", 260, 136, 16);
				self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 85);
				break;
		}
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
			break;
		case 2:
			self->sprite = gf2d_sprite_load_all("images/words/lullaby.png", 255, 61, 16);
			self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 550);
			break;
		case 3:
			self->sprite = gf2d_sprite_load_all("images/words/storm.png", 185, 46, 16);
			self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 550);
			break;
		case 4:
			self->sprite = gf2d_sprite_load_all("images/words/bash.png", 144, 46, 16);
			self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 550);
			break;
		case 5:
			self->sprite = gf2d_sprite_load_all("images/words/dance.png", 180, 46, 16);
			self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 550);
			break;
		case 6:
			self->sprite = gf2d_sprite_load_all("images/words/fireball.png", 292, 51, 16);
			self->position = vector2d(camera_get_position().x + 860, camera_get_position().y + 550);
			break;
		case 7:
			self->sprite = gf2d_sprite_load_all("images/words/slash.png", 181, 46, 16);
			self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 550);
			break;
		case 8:
			self->sprite = gf2d_sprite_load_all("images/words/whistle.png", 260, 51, 16);
			self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 550);
			break;
		case 9:
			self->sprite = gf2d_sprite_load_all("images/words/mm.png", 260, 136, 16);
			self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 500);
			break;
		}
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
			break;
		case 2:
			self->sprite = gf2d_sprite_load_all("images/words/lullaby.png", 255, 61, 16);
			self->position = vector2d(camera_get_position().x + 80, camera_get_position().y + 550);
			break;
		case 3:
			self->sprite = gf2d_sprite_load_all("images/words/storm.png", 185, 46, 16);
			self->position = vector2d(camera_get_position().x + 80, camera_get_position().y + 550);
			break;
		case 4:
			self->sprite = gf2d_sprite_load_all("images/words/bash.png", 144, 46, 16);
			self->position = vector2d(camera_get_position().x + 80, camera_get_position().y + 550);
			break;
		case 5:
			self->sprite = gf2d_sprite_load_all("images/words/dance.png", 180, 46, 16);
			self->position = vector2d(camera_get_position().x + 80, camera_get_position().y + 550);
			break;
		case 6:
			self->sprite = gf2d_sprite_load_all("images/words/fireball.png", 292, 51, 16);
			self->position = vector2d(camera_get_position().x + 60, camera_get_position().y + 550);
			break;
		case 7:
			self->sprite = gf2d_sprite_load_all("images/words/slash.png", 181, 46, 16);
			self->position = vector2d(camera_get_position().x + 80, camera_get_position().y + 550);
			break;
		case 8:
			self->sprite = gf2d_sprite_load_all("images/words/whistle.png", 260, 51, 16);
			self->position = vector2d(camera_get_position().x + 80, camera_get_position().y + 550);
			break;
		case 9:
			self->sprite = gf2d_sprite_load_all("images/words/mm.png", 260, 136, 16);
			self->position = vector2d(camera_get_position().x + 100, camera_get_position().y + 500);
			break;
		}
	}
}

/**/