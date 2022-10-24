#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "curiosity.h"
#include "pile.h"


/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

static void stop(void) {
    char enter = '\0';
    printf ("Appuyer sur entrée pour continuer...\n");
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
}


static int add (int a, int b) { return a + b; }
static int sub (int a, int b) { return a - b; }
static int mult(int a, int b) { return a * b; }


#define NEXT(c) c = c->suivant
int interprete(sequence_t* seq, bool debug) {
	assert(seq);
    printf ("Programme: ");
    afficher(seq);
	printf ("\e[%dC^^^\n", 10);

    if (debug) stop();

    int ret, i = 0;
	cellule_t* node = seq->tete;

	Stack stack = { NULL };

    while (node) { //à modifier: condition de boucle
        switch (node->cmd) {
            case Avancer:
                ret = avance();
                if (ret == VICTOIRE) return VICTOIRE;
                if (ret == RATE)     return RATE;
                break;

			case Gauche: gauche(); break;
			case Droite: droite(); break;

			case Add:  calcul(&stack, add);  break;
			case Sub:  calcul(&stack, sub);  break;
			case Mult: calcul(&stack, mult); break;

			case Pose: pose(pop(&stack)); break;
			case Mesure: stack.head->val = mesure(stack.head->val); break;

            default:
				if ('0' <= node->cmd && node->cmd <= '9') {
					push(&stack, node->cmd - '0');
				} else {
					eprintf("Caractère inconnu: '%c'\n", node->cmd);
				}
        }

		NEXT(node);

        afficherCarte();

		i++;
        printf ("Programme: ");
        afficher(seq);
        printf ("\e[%dC^^^\n", 10 + i * 5);
		
		printf("Stack: ");
		show_stack(&stack);
        printf ("\n");

        if (debug) stop();
    }

    return CIBLERATEE;
}
