#include "dijkstra.h"
#include "animation.h"

/**
 * cout : calcule le coût pour rejoindre le noeud suivant depuis le noeud
 * courant. Ce coût est égal à la distance euclidienne entre les deux noeuds,
 * plus le dénivelé entre ces deux noeuds s'il est positif.
 * 
 * Pré-conditions :
 *  - dans_les_bornes(grille, courant)
 *  - dans_les_bornes(grille, suivant)
 * Post-conditions :
 *  - cout > 0, potentiellement infini (INFINITIY)
 *
 * @param grille heightmap contenant les hauteurs
 * @param courant noeud duquel on part pour calculer le coût
 * @param suivant noeud auquel on arrive pour calculer le coût
 * @return coût pour passer de courant à suivant
 */
static float cout(grille_t grille, coord_t courant, coord_t suivant) {
	float distance; 
	/* Préconditions, les deux noeuds sont dans la grille : */
	if ((!dans_les_bornes(grille,courant)) || (!dans_les_bornes(grille,suivant))) {
		return NULL;        //ou alors on met un message d'erreur
	}
	distance = distance_euclidienne(courant,suivant);
	if (distance >= 0) {
		return distance;
	}
}

/**
 * construire_chemin_vers - Construit le chemin depuis le noeud de départ donné vers le
 * noeud donné. On passe un chemin en entrée-sortie de la fonction, qui est mis à jour
 * par celle-ci.
 *
 * Ce sous-programme fonctionne récursivement :
 *  1. Si le noeud est égal au noeud de départ, on a fini
 *  2. Sinon, on construit le chemin du départ au noeud précédent (appel récursif)
 *  3. Dans tous les cas, on ajoute le noeud au chemin, avec les caractéristiques associées dans visites
 *
 * @param chemin [in/out] chemin dans lequel enregistrer les étapes depuis le départ vers noeud
 * @param visites [in] liste des noeuds visités créée par l'algorithme de Dijkstra
 * @param source noeud de départ du chemin
 * @param noeud noeud vers lequel on veut construire le chemin depuis le départ
 */
// TODO: construire_chemin_vers

float construire_chemin_vers(liste_noeud_t* chemin, liste_noeud_t* visites, coord_t source, coord_t noeud) {
	float cout_chemin = 0;
	coord_t precedent = precedent_noeud_liste(visites, noeud);

	if (memes_coord(noeud,source)) {      //cas de base, C-2
		inserer_noeud_liste(chemin, noeud, noeud, 0.0);		//c'est le noeud de depart par convention il est son propre précédent
		return cout_chemin;
	}
	else {
		construire_chemin_vers(chemin, visites, source, precedent);		//appel récursif C-3
		inserer_noeud_liste(chemin, noeud, precedent, cout_noeud_liste(visites, noeud));
		cout_chemin = cout_chemin + cout_noeud_liste(visites, noeud);
	}
	return cout_chemin;
}


float dijkstra(grille_t grille, coord_t source, coord_t destination, float seuil, liste_noeud_t** chemin) {
	// TODO
	liste_noeud_t* AVisiter = creer_liste();
	liste_noeud_t* visites = creer_liste();
	coord_t** voisins;	// le tableau des voisins
	int n;				// taille du tableau des voisins
	coord_t voisin;
	float delta_prime;		//NB : je me base sur les notations du sujet mais je ne connais pas le raccourci clavier MacOS de delta
	float delta;

	// partie "D"
	inserer_noeud_liste(AVisiter, source, source, 0.0);																		// D-1
	while (est_vide_liste(AVisiter) == false) {																				// D-2
		coord_t courant = min_noeud_liste(AVisiter);																		// D-2.1
		inserer_noeud_liste(visites, courant, precedent_noeud_liste(AVisiter, courant), cout_noeud_liste(AVisiter, courant));	// D-2.2
		supprimer_noeud_liste(AVisiter, courant);																			// D-2.3
		n = get_voisins(grille, courant, seuil, voisins);
		for (int compteur = 0; compteur < n; compteur++) {
			voisin = voisins[compteur];
			if (contient_noeud_liste(visites,voisin) == false) { 															// voisin non visité D-2.4
				delta_prime = cout_noeud_liste(visites, courant) + distance_euclidienne(courant, voisin);					// D-2.4.1
				if (contient_noeud_liste(AVisiter,voisin)) {																// si voisin dans AVisiter, D-2.4.2
					delta = cout_noeud_liste(AVisiter, voisin);
				}
				else {
					delta = INFINITY;
				}
				if (delta_prime < delta) {																					// D-2.4.3
					inserer_noeud_liste(AVisiter, voisin, courant, delta_prime);
				}
			}
			else {
				null;		// si voisin deja visité on ne fait rien
			}
		}
	}
	// partie "C"
	float cout_minimal = construire_chemin_vers(chemin, visites, source, destination);
	return cout_minimal;
}


