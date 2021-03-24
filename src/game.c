#include <SDL.h>

#include <math.h>

#include "simple_logger.h"

#include "gf2d_graphics.h"
#include "gf2d_sprite.h"

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
    
    int mx,my;
    float mf = 0;
    Sprite *mouse;
    Vector4D mouseColor = {255,100,255,200};
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
    //font_init(10);
    entity_manager_init(100);
    
    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);
    level = level_load("levels/exampleLevel.json");
    player_spawn(vector2d(100,100));

	
	ent[2] = entity_new();
	ent[2]->sprite = gf2d_sprite_load_all("images/sword.png", 28, 28, 16);
	ent[2]->position = vector2d(100, 500);
	ent[2]->hitbox = shape_rect_from_vector4d(vector4d(100, 500, 28, 28));
	ent[2]->think = itemthink;
	ent[2]->type = 1;
	ent[3] = entity_new();
	ent[3]->sprite = gf2d_sprite_load_all("images/guitar.png", 28, 28, 16);
	ent[3]->position = vector2d(100, 600);
	ent[3]->hitbox = shape_rect_from_vector4d(vector4d(100, 600, 20, 20));
	ent[3]->think = itemthink;
	ent[3]->type = 2;
	ent[4] = entity_new();
	ent[4]->sprite = gf2d_sprite_load_all("images/wand.png", 20, 20, 16);
	ent[4]->position = vector2d(100, 700);
	ent[4]->hitbox = shape_rect_from_vector4d(vector4d(100, 700, 28, 28));
	ent[4]->think = itemthink;
	ent[4]->type = 3;

	ent[5] = entity_new();
	ent[5]->sprite = gf2d_sprite_load_all("images/troll.png", 64, 64, 16);
	ent[5]->position = vector2d(600, 50);
	ent[5]->hitbox = shape_rect_from_vector4d(vector4d(600, 50, 64, 64));
	ent[5]->think = enemythink;
	ent[5]->type = 1;
	ent[6] = entity_new();
	ent[6]->sprite = gf2d_sprite_load_all("images/troll.png", 64, 64, 16);
	ent[6]->position = vector2d(700, 50);
	ent[6]->hitbox = shape_rect_from_vector4d(vector4d(700, 50, 64, 64));
	ent[6]->think = enemythink;
	ent[6]->type = 2;
	ent[7] = entity_new();
	ent[7]->sprite = gf2d_sprite_load_all("images/troll.png", 64, 64, 16);
	ent[7]->position = vector2d(800, 50);
	ent[7]->hitbox = shape_rect_from_vector4d(vector4d(800, 50, 64, 64));
	ent[7]->think = enemythink;
	ent[7]->type = 3;
	ent[8] = entity_new();
	ent[8]->sprite = gf2d_sprite_load_all("images/troll.png", 64, 64, 16);
	ent[8]->position = vector2d(900, 50);
	ent[8]->hitbox = shape_rect_from_vector4d(vector4d(900, 50, 64, 64));
	ent[8]->think = enemythink;
	ent[8]->type = 4;
	ent[9] = entity_new();
	ent[9]->sprite = gf2d_sprite_load_all("images/troll.png", 64, 64, 16);
	ent[9]->position = vector2d(1000, 50);
	ent[9]->hitbox = shape_rect_from_vector4d(vector4d(1000, 50, 64, 64));
	ent[9]->think = enemythink;
	ent[9]->type = 5;






    //font = font_load("fonts/8bitoperator.ttf",16);
	ent[0] = entity_new();
	ent[0]->think = menuthink;
	ent[1] = entity_new();
	ent[1]->think = selectthink;

	ent[10] = entity_new();
	ent[10]->think = backgroundthink;
	ent[11] = entity_new();
	ent[11]->think = battlethink;
	ent[12] = entity_new();
	ent[12]->think = ba1;
	ent[13] = entity_new();
	ent[13]->think = ba2;
	ent[14] = entity_new();
	ent[14]->think = ba3;
	ent[15] = entity_new();
	ent[15]->think = ba4;
	ent[16] = entity_new();
	ent[16]->think = bselect;


	

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

        level_update(level);
        
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            level_draw(level);

            entity_manager_draw_entities();
            //UI elements last
            gf2d_sprite_draw(
                mouse,
                vector2d(mx,my),
                NULL,
                NULL,
                NULL,
                NULL,
                &mouseColor,
                (int)mf);
        //gfc_line_sprintf(text,"Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
        //font_render(font,text,vector2d(32,32),gfc_color8(255,0,0,255));

        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame

        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
    }
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/