#include "coord.h"

// TODO : implanter le module coord


/* creer_coord :  */
coord_t creer_coord(int x, int y) {
    coord_t c;
    c.x = x;
    c.y = y;
    return c;
}


/* get_x :  */
int get_x(coord_t c) {
    return c.x;
}


/* get_y : */
int get_y(coord_t c) {
    return c.y;
}


/* set_x : */
void set_x(coord_t *c, int x) {
    c->x = x;
}


/* set_y :  */
void set_y(coord_t *c, int y) {
    c->y = y;
}


/* memes_coord : */
bool memes_coord(coord_t c1, coord_t c2) {
    return (c1.x == c2.x) && (c1.y == c2.y);
}


/* translation : */
coord_t translation(coord_t c, int dx, int dy) {
    coord_t res;
    res.x = c.x + dx;
    res.y = c.y + dy;
    return res;
}


/* distance_euclidienne : */
float distance_euclidienne(coord_t c1, coord_t c2) {
    int dx = c2.x - c1.x;
    int dy = c2.y - c1.y;
    return sqrtf((float)(dx * dx + dy * dy));
}
