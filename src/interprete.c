#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "curiosity.h"


/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

void stop(void) {
    char enter = '\0';
    printf ("Appuyer sur entrée pour continuer...\n");
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
}


#define NEXT(c) c = c->suivant
int interprete(sequence_t* seq, bool debug) {
	assert(seq);
    printf ("Programme:");
    afficher(seq);
    printf ("\n");

    if (debug) stop();

    int ret;
	cellule_t* node = seq->tete;

    while (node) { //à modifier: condition de boucle
        switch (node->cmd) {
            case Avancer:
                ret = avance();
                if (ret == VICTOIRE) return VICTOIRE;
                if (ret == RATE)     return RATE;
                break;

			case Gauche: gauche(); break;
			case Droite: droite(); break;

            default:
                eprintf("Caractère inconnu: '%c'\n", node->cmd);
        }

		NEXT(node);

        afficherCarte();
        printf ("Programme:");
        afficher(seq);
        printf ("\n");
        if (debug) stop();
    }

    return CIBLERATEE;
}
