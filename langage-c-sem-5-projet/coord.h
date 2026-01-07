// TODO : écrire la spécification du module coord
// Note : ne pas oublier la garde pour le header

#ifndef COORD_H // Garde            garde inspirée du machin.h du même classeur
#define COORD_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>


/* type coord_t :
    Représente un point du plan par ses coordonnées (x, y) */
typedef struct {
    int x;
    int y;
} coord_t;


/* creer_coord :
    Spécification :
    Entrées : deux entiers x et y
    Sortie  : un coord_t dont l'abscisse vaut x et l'ordonnée vaut y */
coord_t creer_coord(int x, int y);


/* get_x :
    Spécification :
    Entrée  : un coord_t
    Sortie  : l'abscisse du point */
int get_x(coord_t c);


/* get_y :
    Spécification :
    Entrée  : un coord_t
    Sortie  : l'ordonnée du point */
int get_y(coord_t c);


/* set_x :
    Spécification :
    Entrées :
        un pointeur sur coord_t (point à modifier)
        un entier x
    Sortie :
        modifie l'abscisse du point */
void set_x(coord_t *c, int x);


/* set_y :
    Spécification :
    Entrées :
        un pointeur sur coord_t (point à modifier)
        un entier y
    Sortie :
        modifie l'ordonnée du point */
void set_y(coord_t *c, int y);


/* memes_coord :
    Spécification :
    Entrées : deux coord_t
    Sortie  :
        true si les deux points ont les mêmes coordonnées
        false sinon */
bool memes_coord(coord_t c1, coord_t c2);


/* translation :
    Spécification :
    Entrées :
        un coord_t
        deux entiers dx et dy
    Sortie :
        un nouveau coord_t correspondant au point
        translaté de dx et dy */
coord_t translation(coord_t c, int dx, int dy);


/* distance_euclidienne :
    Spécification :
    Entrées :
        deux coord_t
    Sortie :
        un flottant correspondant à la distance euclidienne entre les deux points */
float distance_euclidienne(coord_t c1, coord_t c2);

#endif
