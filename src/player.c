#include "simple_logger.h"

#include "player.h"
#include "camera.h"
#include "shape.h"
#include "simple_json.h"

void player_update(Entity *self);
void player_think(Entity *self);

Uint16 overworld, menu, battle;
Uint16 points, form;
Uint16 slash, whistle, mm, bash, dance, fireball, smite, lullaby, storm;
Uint16 b2, b3, b4;
int spos;
float wait;
ShapeRect hb;
float x, y;
SJson *json, *place, *jx, *jy;

SJString build;
const Uint8 *keys;

Entity *player_spawn(Vector2D position)
{
	Entity *ent;
	overworld = 1;
	menu = 0;
	spos = 8;
	wait = 0;
	points = 3;
	smite = 0;
	lullaby = 0;
	storm = 0;
	bash = 0;
	dance = 0;
	fireball = 0;
	slash = 0;
	whistle = 0;
	mm = 0;
	form = 0;
	b2 = 0;
	b3 = 0;
	b4 = 0;
	ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the player");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_all("images/hero.png", 64, 64, 16);
	vector2d_copy(ent->position, position);
	//ent->frameRate = 0.1;
	//ent->frameCount = 16;
	ent->update = player_update;
	ent->think = player_think;
	ent->rotation.x = 64;
	ent->rotation.y = 64;
	return ent;
}


void player_update(Entity *self)
{
	Vector2D camera;
	Vector2D cameraSize;

	if (!self)return;
	cameraSize = camera_get_dimensions();
	camera.x = (self->position.x + 64) - (cameraSize.x * 0.5);
	camera.y = (self->position.y + 64) - (cameraSize.y * 0.5);
	camera_set_position(camera);
	// apply dampening on velocity
	vector2d_scale(self->velocity, self->velocity, 0.75);
	if (vector2d_magnitude_squared(self->velocity) < 2)
	{
		vector2d_clear(self->velocity);
	}
}

void player_think(Entity *self)
{
	Vector2D camera;
	float speed = 2;
	int mx, my;
	if (!self)return;
	keys = SDL_GetKeyboardState(NULL);
	SDL_GetMouseState(&mx, &my);
	/*camera = camera_get_position();
	mx += camera.x;
	my += camera.y;*/
	self->hitbox = shape_rect_from_vector4d(vector4d(self->position.x, self->position.y, 64, 64));
	hb = self->hitbox;
	switch (form)
	{
		case 1:
			self->sprite = gf2d_sprite_load_all("images/khero.png", 64, 64, 16);
			break;
		case 2:
			self->sprite = gf2d_sprite_load_all("images/bhero.png", 64, 64, 16);
			break;
		case 3:
			self->sprite = gf2d_sprite_load_all("images/whero.png", 64, 64, 16);
			break;
	}
	if (wait > 0)
	{
		wait -= 0.1;
	}
	// check for motion
	if (overworld == 1)
	{
		if (keys[SDL_SCANCODE_W])
		{
			self->position.y -= speed;
		}
		if (keys[SDL_SCANCODE_A])
		{
			self->position.x -= speed;
		}
		if (keys[SDL_SCANCODE_S])
		{
			self->position.y += speed;
		}
		if (keys[SDL_SCANCODE_D])
		{
			self->position.x += speed;
		}
		if (keys[SDL_SCANCODE_O] && wait <= 0)
		{
			wait = 2;
			json = sj_object_new();
			place = sj_object_new();
			jx = sj_new_float(self->position.x);
			jy = sj_new_float(self->position.y);
			sj_object_insert(place, "x", jx);
			sj_object_insert(place, "y", jy);
			sj_object_insert(json, "place", place);
			sj_echo(json);
			sj_save(json, "json/place.json");
		}
		if (keys[SDL_SCANCODE_P] && wait <= 0)
		{
			wait = 2;
			json = sj_load("json/place.json");
			place = sj_object_get_value(json, "place");
			jx = sj_object_get_value(place, "x");
			jy = sj_object_get_value(place, "y");
			sj_get_float_value(jx, &x);
			sj_get_float_value(jy, &y);
			self->position.x = x;
			self->position.y = y;

		}
		if (wait <= 0)
		{
			if (keys[SDL_SCANCODE_E])
			{
				overworld = 0;
				menu = 1;
				wait = 2;
			}
		}
	}
	//slog("%f", wait);

}
ShapeRect hitbox()
{
	return hb;
}
void change(Uint16 type)
{
	form = type;
}
void menuthink(Entity *self)
{
	self->position = vector2d(camera_get_position().x, camera_get_position().y);
	if (menu == 1)
	{
		self->sprite = gf2d_sprite_load_all("images/skill tree.png", 1200, 720, 16);
		if (keys[SDL_SCANCODE_E])
		{
			self->sprite = gf2d_sprite_load_all("images/blank.png", 1, 1, 16);
		}
	}
}
void backgroundthink(Entity *self)
{
	self->position = vector2d(camera_get_position().x, camera_get_position().y);
	if (battle == 1)
	{
		self->sprite = gf2d_sprite_load_all("images/battleback.png", 1200, 720, 16);
	}
	if (battle == 0)
	{
		gf2d_sprite_delete(self->sprite);
	}

}
void selectthink(Entity *self)
{
	if (menu == 1)
	{
		self->sprite = gf2d_sprite_load_all("images/highlight.png", 311, 166, 16);
		if (wait <= 0)
		{
			if (keys[SDL_SCANCODE_W] && spos > 3)
			{
				spos -= 3;
				wait = 2;
			}
			if (keys[SDL_SCANCODE_A] && spos != 1 && spos != 4 && spos != 7)
			{
				spos -= 1;
				wait = 2;
			}
			if (keys[SDL_SCANCODE_S] && spos < 7)
			{
				spos += 3;
				wait = 2;
			}
			if (keys[SDL_SCANCODE_D] && spos != 3 && spos != 6 && spos != 9)
			{
				spos += 1;
				wait = 2;
			}
			if (keys[SDL_SCANCODE_E])
			{
				overworld = 1;
				menu = 0;
				wait = 2;
				gf2d_sprite_delete(self->sprite);
			}
			if (keys[SDL_SCANCODE_SPACE])
			{
				switch (spos)
				{
				case 1:
					if (smite == 0 && points > 0 && bash == 1)
					{
						if (b2 == 0)
							b2 = 1;
						else if (b3 == 0)
							b3 = 1;
						else
							b4 = 1;
						points -= 1;
						smite = 1;
						slog("Smite unlocked");
					}
					break;
				case 2:
					if (lullaby == 0 && points > 0 && dance == 1)
					{
						if (b2 == 0)
							b2 = 2;
						else if (b3 == 0)
							b3 = 2;
						else
							b4 = 2;
						points -= 1;
						lullaby = 1;
						slog("Lullaby unlocked");
					}
					break;
				case 3:
					if (storm == 0 && points > 0 && fireball == 1)
					{
						if (b2 == 0)
							b2 = 3;
						else if (b3 == 0)
							b3 = 3;
						else
							b4 = 3;
						points -= 1;
						storm = 1;
						slog("Storm unlocked");
					}
					break;
				case 4:
					if (bash == 0 && points > 0 && slash == 1)
					{
						if (b2 == 0)
							b2 = 4;
						else if (b3 == 0)
							b3 = 4;
						else
							b4 = 4;
						points -= 1;
						bash = 1;
						slog("Bash unlocked");
					}
					break;
				case 5:
					if (dance == 0 && points > 0 && whistle == 1)
					{
						if (b2 == 0)
							b2 = 5;
						else if (b3 == 0)
							b3 = 5;
						else
							b4 = 5;
						points -= 1;
						dance = 1;
						slog("Dance unlocked");
					}
					break;
				case 6:
					if (fireball == 0 && points > 0 && mm == 1)
					{
						if (b2 == 0)
							b2 = 6;
						else if (b3 == 0)
							b3 = 6;
						else
							b4 = 6;
						points -= 1;
						fireball = 1;
						slog("Fireball unlocked");
					}
					break;
				case 7:
					if (slash == 0 && points > 0)
					{
						if (b2 == 0)
							b2 = 7;
						else if (b3 == 0)
							b3 = 7;
						else
							b4 = 7;
						points -= 1;
						slash = 1;
						slog("Slash unlocked");
					}
					break;
				case 8:
					if (whistle == 0 && points > 0)
					{
						if (b2 == 0)
							b2 = 8;
						else if (b3 == 0)
							b3 = 8;
						else
							b4 = 8;
						points -= 1;
						whistle = 1;
						slog("Whistle unlocked");
					}
					break;
				case 9:
					if (mm == 0 && points > 0)
					{
						if (b2 == 0)
							b2 = 9;
						else if (b3 == 0)
							b3 = 9;
						else
							b4 = 9;
						points -= 1;
						mm = 1;
						slog("Magic Missile unlocked");
					}
					break;
				}
			}
		}

		switch (spos)
		{
			case 1:
				self->position = vector2d(camera_get_position().x + 20, camera_get_position().y + 75);
				break;
			case 2:
				self->position = vector2d(camera_get_position().x + 450, camera_get_position().y + 75);
				break;
			case 3:
				self->position = vector2d(camera_get_position().x + 880, camera_get_position().y + 75);
				break;
			case 4:
				self->position = vector2d(camera_get_position().x + 20, camera_get_position().y + 285);
				break;
			case 5:
				self->position = vector2d(camera_get_position().x + 450, camera_get_position().y + 285);
				break;
			case 6:
				self->position = vector2d(camera_get_position().x + 835, camera_get_position().y + 285);
				break;
			case 7:
				self->position = vector2d(camera_get_position().x + 20, camera_get_position().y + 495);
				break;
			case 8:
				self->position = vector2d(camera_get_position().x + 450, camera_get_position().y + 495);
				break;
			case 9:
				self->position = vector2d(camera_get_position().x + 850, camera_get_position().y + 495);
				break;
		}
	}
}

void battlestart()
{
	overworld = 0;
	menu = 0;
	battle = 1;
}
void battleend()
{
	overworld = 1;
	battle = 0;
}
Uint16 B2()
{
	return b2;
}
Uint16 B3()
{
	return b3;
}
Uint16 B4()
{
	return b4;
}

/**/