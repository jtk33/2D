#include <SDL.h>

#include <math.h>

#include "simple_logger.h"

#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "gf2d_audio.h"

#include "font.h"
#include "camera.h"
#include "entity.h"
#include "player.h"
#include "level.h"
#include "battle.h"


int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    Level *level;
    Font *font;
    TextLine text;
	Mix_Music *music;
	Uint16 currlevel;

	int mx,my;
    float mf = 0;
	Entity *ent[50] = { 0 };
    /*program initializtion*/
    init_logger("gf2d.log");
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        1200,
        720,
        1200,
        720,
        vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(16);
    camera_set_dimensions(vector2d(1200,720));
    camera_set_position(vector2d(0,0));
    gf2d_sprite_init(1024);
	gf2d_audio_init(256, 16, 4, 2, 1, 1);

    //font_init(10);
    entity_manager_init(100);
    
    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/
    level = level_load("levels/exampleLevel.json");
	currlevel = 1;
    player_spawn(vector2d(100,100));

	
	ent[2] = entity_new();
	ent[2]->sprite = gf2d_sprite_load_all("images/sword.png", 28, 28, 16);
	ent[2]->position = vector2d(100, 500);
	ent[2]->hitbox = shape_rect_from_vector4d(vector4d(100, 500, 28, 28));
	ent[2]->think = itemthink;
	ent[2]->type = 1;
	ent[2]->level = 1;
	ent[2]->realpos = vector2d(100, 500);
	ent[3] = entity_new();
	ent[3]->sprite = gf2d_sprite_load_all("images/guitar.png", 28, 28, 16);
	ent[3]->position = vector2d(100, 600);
	ent[3]->hitbox = shape_rect_from_vector4d(vector4d(100, 600, 20, 20));
	ent[3]->think = itemthink;
	ent[3]->type = 2;
	ent[3]->level = 1;
	ent[3]->realpos = vector2d(100, 600);
	ent[4] = entity_new();
	ent[4]->sprite = gf2d_sprite_load_all("images/wand.png", 20, 20, 16);
	ent[4]->position = vector2d(100, 700);
	ent[4]->hitbox = shape_rect_from_vector4d(vector4d(100, 700, 28, 28));
	ent[4]->think = itemthink;
	ent[4]->type = 3;
	ent[4]->level = 1;
	ent[4]->realpos = vector2d(100, 700);

	ent[5] = entity_new();
	ent[5]->sprite = gf2d_sprite_load_all("images/troll.png", 64, 64, 16);
	ent[5]->position = vector2d(600, 50);
	ent[5]->hitbox = shape_rect_from_vector4d(vector4d(600, 50, 64, 64));
	ent[5]->think = enemythink;
	ent[5]->type = 1;
	ent[5]->level = 1;
	ent[5]->realpos = vector2d(600, 50);
	ent[6] = entity_new();
	ent[6]->sprite = gf2d_sprite_load_all("images/troll.png", 64, 64, 16);
	ent[6]->position = vector2d(800, 500);
	ent[6]->hitbox = shape_rect_from_vector4d(vector4d(800, 500, 64, 64));
	ent[6]->think = enemythink;
	ent[6]->type = 2;
	ent[6]->level = 1;
	ent[6]->realpos = vector2d(800, 500);
	ent[7] = entity_new();
	ent[7]->sprite = gf2d_sprite_load_all("images/troll.png", 64, 64, 16);
	ent[7]->position = vector2d(900, 200);
	ent[7]->hitbox = shape_rect_from_vector4d(vector4d(900, 200, 64, 64));
	ent[7]->think = enemythink;
	ent[7]->type = 3;
	ent[7]->level = 1;
	ent[7]->realpos = vector2d(900, 200);
	ent[8] = entity_new();
	ent[8]->sprite = gf2d_sprite_load_all("images/troll.png", 64, 64, 16);
	ent[8]->position = vector2d(1200, 300);
	ent[8]->hitbox = shape_rect_from_vector4d(vector4d(1200, 300, 64, 64));
	ent[8]->think = enemythink;
	ent[8]->type = 4;
	ent[8]->level = 1;
	ent[8]->realpos = vector2d(1200, 300);
	ent[9] = entity_new();
	ent[9]->sprite = gf2d_sprite_load_all("images/troll.png", 64, 64, 16);
	ent[9]->position = vector2d(1500, 800);
	ent[9]->hitbox = shape_rect_from_vector4d(vector4d(1500, 800, 64, 64));
	ent[9]->think = enemythink;
	ent[9]->type = 5;
	ent[9]->level = 1;
	ent[9]->realpos = vector2d(1500, 800);


	ent[10] = entity_new();
	ent[10]->sprite = gf2d_sprite_load_all("images/troll.png", 64, 64, 16);
	ent[10]->position = vector2d(700, 500);
	ent[10]->hitbox = shape_rect_from_vector4d(vector4d(700, 500, 64, 64));
	ent[10]->think = enemythink;
	ent[10]->type = 2;
	ent[10]->level = 2;
	ent[10]->realpos = vector2d(700, 500);
	ent[11] = entity_new();
	ent[11]->sprite = gf2d_sprite_load_all("images/troll.png", 64, 64, 16);
	ent[11]->position = vector2d(400, 700);
	ent[11]->hitbox = shape_rect_from_vector4d(vector4d(400, 700, 64, 64));
	ent[11]->think = enemythink;
	ent[11]->type = 2;
	ent[11]->level = 2;
	ent[11]->realpos = vector2d(400, 700);
	ent[12] = entity_new();
	ent[12]->sprite = gf2d_sprite_load_all("images/troll.png", 64, 64, 16);
	ent[12]->position = vector2d(900, 100);
	ent[12]->hitbox = shape_rect_from_vector4d(vector4d(900, 100, 64, 64));
	ent[12]->think = enemythink;
	ent[12]->type = 2;
	ent[12]->level = 2;
	ent[12]->realpos = vector2d(900, 100);
	ent[13] = entity_new();
	ent[13]->sprite = gf2d_sprite_load_all("images/troll.png", 64, 64, 16);
	ent[13]->position = vector2d(1400, 900);
	ent[13]->hitbox = shape_rect_from_vector4d(vector4d(1400, 900, 64, 64));
	ent[13]->think = enemythink;
	ent[13]->type = 2;
	ent[13]->level = 2;
	ent[13]->realpos = vector2d(1400, 900);
	ent[14] = entity_new();
	ent[14]->sprite = gf2d_sprite_load_all("images/troll.png", 64, 64, 16);
	ent[14]->position = vector2d(1600, 200);
	ent[14]->hitbox = shape_rect_from_vector4d(vector4d(1600, 200, 64, 64));
	ent[14]->think = enemythink;
	ent[14]->type = 2;
	ent[14]->level = 2;
	ent[14]->realpos = vector2d(1600, 200);

	ent[15] = entity_new();
	ent[15]->sprite = gf2d_sprite_load_all("images/troll.png", 64, 64, 16);
	ent[15]->position = vector2d(1000, 400);
	ent[15]->hitbox = shape_rect_from_vector4d(vector4d(1000, 400, 64, 64));
	ent[15]->think = enemythink;
	ent[15]->type = 4;
	ent[15]->level = 3;
	ent[15]->realpos = vector2d(1000, 400);
	ent[16] = entity_new();
	ent[16]->sprite = gf2d_sprite_load_all("images/troll.png", 64, 64, 16);
	ent[16]->position = vector2d(600, 900);
	ent[16]->hitbox = shape_rect_from_vector4d(vector4d(600, 900, 64, 64));
	ent[16]->think = enemythink;
	ent[16]->type = 4;
	ent[16]->level = 3;
	ent[16]->realpos = vector2d(600, 900);
	ent[17] = entity_new();
	ent[17]->sprite = gf2d_sprite_load_all("images/troll.png", 64, 64, 16);
	ent[17]->position = vector2d(1700, 700);
	ent[17]->hitbox = shape_rect_from_vector4d(vector4d(1700, 700, 64, 64));
	ent[17]->think = enemythink;
	ent[17]->type = 4;
	ent[17]->level = 3;
	ent[17]->realpos = vector2d(1700, 700);
	ent[18] = entity_new();
	ent[18]->sprite = gf2d_sprite_load_all("images/troll.png", 64, 64, 16);
	ent[18]->position = vector2d(1400, 500);
	ent[18]->hitbox = shape_rect_from_vector4d(vector4d(1400, 500, 64, 64));
	ent[18]->think = enemythink;
	ent[18]->type = 4;
	ent[18]->level = 3;
	ent[18]->realpos = vector2d(1400, 500);
	ent[19] = entity_new();
	ent[19]->sprite = gf2d_sprite_load_all("images/troll.png", 64, 64, 16);
	ent[19]->position = vector2d(300, 600);
	ent[19]->hitbox = shape_rect_from_vector4d(vector4d(300, 600, 64, 64));
	ent[19]->think = enemythink;
	ent[19]->type = 4;
	ent[19]->level = 3;
	ent[19]->realpos = vector2d(300, 600);
	ent[20] = entity_new();
	ent[20]->sprite = gf2d_sprite_load_all("images/troll.png", 64, 64, 16);
	ent[20]->position = vector2d(500, 200);
	ent[20]->hitbox = shape_rect_from_vector4d(vector4d(500, 200, 64, 64));
	ent[20]->think = enemythink;
	ent[20]->type = 4;
	ent[20]->level = 3;
	ent[20]->realpos = vector2d(500, 200);


    //font = font_load("fonts/8bitoperator.ttf",16);
	ent[0] = entity_new();
	ent[0]->think = menuthink;
	ent[1] = entity_new();
	ent[1]->think = selectthink;

	ent[40] = entity_new();
	ent[40]->think = backgroundthink;
	ent[41] = entity_new();
	ent[41]->think = battlethink;
	ent[42] = entity_new();
	ent[42]->think = ba1;
	ent[43] = entity_new();
	ent[43]->think = ba2;
	ent[44] = entity_new();
	ent[44]->think = ba3;
	ent[45] = entity_new();
	ent[45]->think = ba4;
	ent[46] = entity_new();
	ent[46]->think = bselect;


	

    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
        mf+=0.1;
        if (mf >= 16.0)mf = 0;
        entity_manager_think_entities();
        entity_manager_update_entities();
		//slog("%f", ent[2]->hitbox.y);
		if (currlevel != currentLevel())
		{
			switch (currentLevel())
			{
			case 1:
				level = level_load("levels/exampleLevel.json");
				currlevel = currentLevel();
				break;
			case 2:
				level = level_load("levels/snowlevel.json");
				currlevel = currentLevel();
				break;
			case 3:
				level = level_load("levels/scorched.json");
				currlevel = currentLevel();
				break;
			}
		}
        level_update(level);
        
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            level_draw(level);

            entity_manager_draw_entities();
            //UI elements last
          
        //gfc_line_sprintf(text,"Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
        //font_render(font,text,vector2d(32,32),gfc_color8(255,0,0,255));

        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame

        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
    }
	Mix_HaltMusic();
	Mix_FreeMusic(music);
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/