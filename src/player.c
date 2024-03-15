// FILE OBTAINED FROM: https://github.com/flightcrank/asteroids/blob/master/asteroids/player.c
//player.c

#include <stdio.h>
#include "display.h"
#include "player.h"

void init_player(struct player* p) {
	
	int i = 0;
	struct vector2d translation = {SCREEN_WIDTH, SCREEN_HEIGHT};
	
	p->hit_radius = 15;
	p->lives = 3;
	p->location.x = 50;
	p->location.y = 50;
	p->velocity.x = 0;
	p->velocity.y = 0;
	p->obj_vert[0].x = 0;
	p->obj_vert[0].y = 1.5;
	p->obj_vert[1].x = -1;
	p->obj_vert[1].y = -1;
	p->obj_vert[2].x = 1;
	p->obj_vert[2].y = -1;

	//convert player verts from object space to world space
	for(i = 0; i < P_VERTS; i++) {

		multiply_vector(&p->obj_vert[i], -1);
		multiply_vector(&p->obj_vert[i], 6);
		add_vector(&p->world_vert[i], &p->obj_vert[i]);
		add_vector(&p->world_vert[i], &translation);
	}
	
	for(i = 0; i < BULLETS; i++) {
		
		p->bullets[i].alive = FALSE;
	}
}

void apply_force(struct vector2d* velocity, struct vector2d v) {

	add_vector(velocity, &v);
}

struct vector2d get_direction(struct player* p) {

	struct vector2d direction = p->obj_vert[0];
	normalise_vector(&direction);

	return direction;
}

void shoot_bullet(struct player* p) {
	
	int i = 0;

	for (i = 0; i < BULLETS; i++) {
		
		if (p->bullets[i].alive == FALSE) {
			
			p->bullets[i].alive = TRUE;
			p->bullets[i].location = p->world_vert[0];
			p->bullets[i].velocity = get_direction(p);
			multiply_vector(&p->bullets[i].velocity, 4.1);
			break;
		}
	}
}

void draw_player(struct player* p) {
	
	int i = 0;
	
	if (p->lives > 0) {

		drawLine(p->old_world_vert[0].x, p->old_world_vert[0].y, p->old_world_vert[1].x, p->old_world_vert[1].y, 0);
		drawLine(p->old_world_vert[1].x, p->old_world_vert[1].y, p->old_world_vert[2].x, p->old_world_vert[2].y, 0);
		drawLine(p->old_world_vert[2].x, p->old_world_vert[2].y, p->old_world_vert[0].x, p->old_world_vert[0].y, 0);

		drawLine(p->world_vert[0].x, p->world_vert[0].y, p->world_vert[1].x, p->world_vert[1].y, 0xff);
		drawLine(p->world_vert[1].x, p->world_vert[1].y, p->world_vert[2].x, p->world_vert[2].y, 0xff);
		drawLine(p->world_vert[2].x, p->world_vert[2].y, p->world_vert[0].x, p->world_vert[0].y, 0xff);

	}

	// Draws the bullets
	for (i = 0; i < BULLETS; i++) {

		if (p->bullets[i].alive == TRUE) {

			// Redraws previous position as background colour
			drawRectangle(p->bullets[i].old_location.x, p->bullets[i].old_location.y, 1, 1, 0);

			// Draws new bullet position
			drawRectangle(p->bullets[i].location.x, p->bullets[i].location.y, 1, 1, 0xfff);

		}
	}

}

void update_player(struct player* p) {
	
	limit_vector(&p->velocity, 2);
	add_vector(&p->location, &p->velocity);
	
	struct vector2d translation = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

	int i = 0; 

	for (i =0; i < P_VERTS; i++) {

		p->old_world_vert[i] = p->world_vert[i];		
		p->world_vert[i] = add_vector_new(&p->obj_vert[i], &p->location);	
		add_vector(&p->world_vert[i], &translation);
	}
	
	for (i = 0; i < BULLETS; i++) {
		
		// Saves old location
		p->bullets[i].old_location = p->bullets[i].location;

		// Moves bullets
		add_vector(&p->bullets[i].location, &p->bullets[i].velocity);

	}
}

// Rotates player
void rotate_player(struct player* p, float degrees) {
	
	int i = 0;

	for (i =0; i < P_VERTS; i++) {
	
		rotate_vector(&p->obj_vert[i], degrees);
	}
}

void bounds_player(struct player* p) {
	
	int i = 0;
	
	// Code for player looping around the screen
	if (p->location.x > SCREEN_WIDTH) {
		
		p->location.x = 1;
	}
	
	if (p->location.x < 1) {
		
		p->location.x = SCREEN_WIDTH;
	}

	if (p->location.y < 1) {
		
		p->location.y = SCREEN_HEIGHT;
	}
	
	if (p->location.y > SCREEN_HEIGHT) {
		
		p->location.y = 1;
	}

	//bullet is out of bounds, reset bullet to be shot again
	//bullets are in world space
	for (i = 0; i < BULLETS; i++) {
		
		if (p->bullets[i].location.x < 0 || p->bullets[i].location.x > SCREEN_WIDTH) {
			
			p->bullets[i].alive = FALSE;
		}
		
		if (p->bullets[i].location.y < 0 || p->bullets[i].location.y > SCREEN_HEIGHT) {
			
			p->bullets[i].alive = FALSE;
		}
	}
}

