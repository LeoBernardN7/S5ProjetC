#define _GNU_SOURCE
#include "liste_noeud.h"
#include <stdlib.h>
#include <math.h>

/* TODO */

/* Structure liste_noeud (structure équivalente au "private" en ada)    */

typedef struct cellule_noeud {
    coord_t noeud;
    coord_t precedent;
    float cout;
    struct cellule_noeud *suivant;
} cellule_noeud_t;

struct liste_noeud {
    cellule_noeud_t *tete;
};



/* creer_liste : crée une liste de noeuds, initialement vide */
liste_noeud_t *creer_liste(void){
    liste_noeud_t *liste = malloc(sizeof(liste_noeud_t));
    if (liste == NULL) {
        return NULL;
    }
    liste->tete = NULL;
    return liste;
}

/* detruire_liste : détruit la liste passée en paramètre */
void detruire_liste(liste_noeud_t **liste_ptr) {
    
    cellule_noeud_t *courant;
    cellule_noeud_t *suivant;

    if (liste_ptr == NULL || *liste_ptr == NULL) {
        return;
    }

    courant = (*liste_ptr)->tete;
    while (courant != NULL) {
        suivant = courant->suivant;             // NB: "courant->suivant" équivaut à "(*courant).suivant", qui se rapproche de "pointeur.all.valeur" en ada, mais plus rapide à écrire
        free(courant);
        courant = suivant;
    }

    free(*liste_ptr);
    *liste_ptr = NULL;
}


/* fonction interne d'accès à une cellule précise de la liste, utile pour les fonctions après */
static cellule_noeud_t *chercher_cellule(const liste_noeud_t *liste, coord_t noeud) {
    
    cellule_noeud_t *courant = liste->tete;
    while (courant != NULL) {
        if (memes_coord(courant->noeud, noeud)) {
            return courant;
        }
        courant = courant->suivant;
    }
    return NULL;
}

/* est_vide_liste : test si la liste passée en paramètre est vide */
bool est_vide_liste(const liste_noeud_t *liste) {

    return liste->tete == NULL;
}

/* contient_noeud_liste : test si le noeud donné appartient à la liste donnée */
bool contient_noeud_liste(const liste_noeud_t *liste, coord_t noeud) {

    return chercher_cellule(liste, noeud) != NULL;
}

/* contient_arrete_liste : test si l'arrête donnée appartient à la liste donnée */
bool contient_arrete_liste(const liste_noeud_t *liste, coord_t source, coord_t destination) {

    cellule_noeud_t *dest_cellule;
    if (!contient_noeud_liste(liste, source)) {
        return false;
    }

    dest_cellule = chercher_cellule(liste, destination);
    if (dest_cellule == NULL) {
        return false;
    }

    return memes_coord(dest_cellule->precedent, source);
}

/* cout_noeud_liste : récupère le coût associé au noeud donné dans la liste donnée */
float cout_noeud_liste(const liste_noeud_t *liste, coord_t noeud) {

    cellule_noeud_t *cellule = chercher_cellule(liste, noeud);
    if (cellule == NULL) {
        return INFINITY;
    }
    return cellule->cout;
}

/* precedent_noeud_liste : récupère le noeud précédent associé au noeud donné dans la liste donnée */
coord_t precedent_noeud_liste(const liste_noeud_t *liste, coord_t noeud) {

    coord_t c;
    cellule_noeud_t *cellule = chercher_cellule(liste, noeud);

    //Si le noeud n'existe pas, retourne des coordonnées négatives
    if (cellule == NULL) {
        set_x(&c, -1);
        set_y(&c, -1);
        return c;
    }
    return cellule->precedent;
}

/* min_noeud_liste : trouve le (un) noeud de la liste dont le coût heuristique associé est le plus petit */
// Précondition: !est_vide_liste(liste)
coord_t min_noeud_liste(const liste_noeud_t *liste) {

    cellule_noeud_t *courant = liste->tete;
    cellule_noeud_t *min_cellule;

    min_cellule = courant;
    courant = courant->suivant;

    while (courant != NULL) {
        if (courant->cout < min_cellule->cout) {
            min_cellule = courant;
        }
        courant = courant->suivant;
    }

    return min_cellule->noeud;
}

/* inserer_noeud_liste : modifie les valeurs associées au noeud donné dans la liste donnée, et ajoute le noeud s'il n'existe pas déjà */
void inserer_noeud_liste(liste_noeud_t *liste, coord_t noeud, coord_t precedent, float cout) {

    cellule_noeud_t *cellule = chercher_cellule(liste, noeud);

    if (cellule != NULL) {
        cellule->precedent = precedent;
        cellule->cout = cout;
        return;
    }

    cellule = malloc(sizeof(cellule_noeud_t));
    if (cellule == NULL) {
        return;
    }

    cellule->noeud = noeud;
    cellule->precedent = precedent;
    cellule->cout = cout;
    cellule->suivant = liste->tete;
    liste->tete = cellule;
}

/* supprimer_noeud_liste : supprime le noeud donné de la liste. Si le noeud n'est pas dans la liste, ne fait rien */
void supprimer_noeud_liste(liste_noeud_t *liste, coord_t noeud) {

    cellule_noeud_t *courant = liste->tete;
    cellule_noeud_t *precedent = NULL;

    while (courant != NULL) {
        if (memes_coord(courant->noeud, noeud)) {
            if (precedent == NULL) {
                liste->tete = courant->suivant;
            } else {
                precedent->suivant = courant->suivant;
            }
            free(courant);
            return;
        }
        precedent = courant;
        courant = courant->suivant;
    }
}


