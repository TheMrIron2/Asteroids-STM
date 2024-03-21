// FILE OBTAINED FROM: https://github.com/flightcrank/asteroids/blob/master/asteroids/player.h
//player.h

#include "vector.h"

#define P_VERTS 3
	
enum boolean {TRUE, FALSE};

struct player {
	char symbol;
	struct vector2d location;
	struct vector2d velocity;
	struct vector2d obj_vert[P_VERTS];
	struct vector2d world_vert[P_VERTS];
	struct vector2d old_world_vert[P_VERTS];
};

void init_player(struct player* p);
void draw_player(struct player* p);
void update_player(struct player* p);
void bounds_player(struct player* p);
void apply_force(struct vector2d* velocity, struct vector2d v);
void rotate_player(struct player* p, float degrees);
struct vector2d get_direction(struct player* p);

