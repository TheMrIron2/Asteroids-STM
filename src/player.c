// FILE OBTAINED FROM: https://github.com/flightcrank/asteroids/blob/master/asteroids/player.c
//player.c

#include <stdio.h>
#include "display.h"
#include "player.h"

#define player_hitbox 10

void init_player(struct player* p) {
	
	int i = 0;
	struct vector2d translation = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

	p->symbol = 'X';
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

		// Points the player up
		multiply_vector(&p->obj_vert[i], -1);
		multiply_vector(&p->obj_vert[i], 6);
		add_vector(&p->world_vert[i], &p->obj_vert[i]);
		add_vector(&p->world_vert[i], &translation);
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

void draw_player(struct player* p) {
	
	// Draws over old position with black
	drawLine(p->old_world_vert[0].x, p->old_world_vert[0].y, p->old_world_vert[1].x, p->old_world_vert[1].y, 0);
	drawLine(p->old_world_vert[1].x, p->old_world_vert[1].y, p->old_world_vert[2].x, p->old_world_vert[2].y, 0);
	drawLine(p->old_world_vert[2].x, p->old_world_vert[2].y, p->old_world_vert[0].x, p->old_world_vert[0].y, 0);

	// Draws new position
	drawLine(p->world_vert[0].x, p->world_vert[0].y, p->world_vert[1].x, p->world_vert[1].y, 0xff);
	drawLine(p->world_vert[1].x, p->world_vert[1].y, p->world_vert[2].x, p->world_vert[2].y, 0xff);
	drawLine(p->world_vert[2].x, p->world_vert[2].y, p->world_vert[0].x, p->world_vert[0].y, 0xff);

}

void update_player(struct player* p) {
	
	limit_vector(&p->velocity, 2);
	add_vector(&p->location, &p->velocity);
	
	int i = 0; 

	for (i =0; i < P_VERTS; i++) {

		// Saves old position of vertices
		p->old_world_vert[i] = p->world_vert[i];

		// Moves vertices to new position	
		p->world_vert[i] = add_vector_new(&p->obj_vert[i], &p->location);

		// Checks if any vertices are offscreen and moves them back onscreen
		if (p->world_vert[i].y > SCREEN_HEIGHT) {
			p->world_vert[i].y -= SCREEN_HEIGHT;
		}
		if (p->world_vert[i].y < 0) {
			p->world_vert[i].y += SCREEN_HEIGHT;
		}
		if (p->world_vert[i].x > SCREEN_WIDTH) {
			p->world_vert[i].x -= SCREEN_WIDTH;
		}
		if (p->world_vert[i].x < 0) {
			p->world_vert[i].x += SCREEN_WIDTH;
		}
		
	}

	if (p->symbol == 'X') {
		p->symbol = 'O';
	}
	else {
		p->symbol = 'X';
	}
}

// Rotates player
void rotate_player(struct player* p, float degrees) {
	
	int i = 0;

	for (i = 0; i < P_VERTS; i++) {
	
		rotate_vector(&p->obj_vert[i], degrees);
	}
}

void bounds_player(struct player* p) {

	// Code for player looping around the screen
	if ((p->location.x + player_hitbox) > SCREEN_WIDTH) {
		
		// Instead of setting the location with player_hitbox, I need to hardcode it
		// I have no idea why. I want to scream.
		p->location.x = 15;
	}
	
	if ((p->location.x - player_hitbox) < 1) {
		
		p->location.x = SCREEN_WIDTH - player_hitbox;
	}

	if ((p->location.y - player_hitbox) < 1) {
		
		p->location.y = SCREEN_HEIGHT - player_hitbox;
	}
	
	if ((p->location.y + player_hitbox) > SCREEN_HEIGHT) {
		
		p->location.y = 15;
	}
}