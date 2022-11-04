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
int interprete(sequence_t* seq, Stack* stack, bool debug) {
	assert(seq);
    printf ("Programme: ");
    afficher(seq);
	printf ("\e[%dC^^^\n", 10);

    if (debug) stop();

    int ret, i = 0;
	cellule_t* node = seq->tete;
	sequence_t* sub_sequence;

    while (node) {
        switch (node->cmd) {
            case Avancer:
                ret = avance();
                if (ret == VICTOIRE) return VICTOIRE;
                if (ret == RATE)     return RATE;
                break;

			case Gauche: gauche(); break;
			case Droite: droite(); break;

			case Add:  calcul(stack, add);  break;
			case Sub:  calcul(stack, sub);  break;
			case Mult: calcul(stack, mult); break;

			case Pose: pose(pop(stack)); break;
			case Mesure: stack->head->val = mesure(stack->head->val); break;

			case SwapHead:   swap_head(stack);  break;
			case CloneHead:  clone_head(stack); break;
			case IgnoreHead: pop(stack);        break;

			case LoadSeq:
				 push_seq(stack, node->sous_sequence);
				 /* node->sous_sequence = NULL; */
			 break;

			case EvalIf:
				// false block (head) -> true block -> key
				// GET RID OF THE KEY **BEFORE** EVALUATING THE CODE
				// YOU FUCKING MORON !!!!
				if (stack->head->next->next->val) {
					pop(stack);  // ignore false block
					sub_sequence = pop_seq(stack);
					pop(stack);  // get rid of key
					ret = interprete(sub_sequence, stack, debug);
				} else {
					sub_sequence = pop_seq(stack);
					ret = interprete(sub_sequence, stack, debug);
					pop(stack);  // get rid of key
					pop(stack);  // ignore true block
				}
                if (ret == VICTOIRE) return VICTOIRE;
                if (ret == RATE)     return RATE;
			break;

			case RawEval:
				sub_sequence = pop_seq(stack);
				ret = interprete(sub_sequence, stack, debug);
                if (ret == VICTOIRE) return VICTOIRE;
                if (ret == RATE)     return RATE;
			break;

			case Loop:
				if (stack->head->val == 0) {
					pop_seq(stack);  // delete the loop code block.
					pop(stack);  // delete the number of remaining iter
				} else {
					stack->head->val--;
					ret = interprete(
							stack->head->next->sous_sequence,
							stack, debug);
					if (ret == VICTOIRE) return VICTOIRE;
					if (ret == RATE)     return RATE;
					goto StayOnCurrentNode;
				}
			break;

			case Rotation: rotation(stack, pop(stack), pop(stack)); break;

            default:
				if ('0' <= node->cmd && node->cmd <= '9') {
					push(stack, node->cmd - '0');
				} else {
					eprintf("Caractère inconnu: '%c'\n", node->cmd);
				}
        }

		NEXT(node);
		i++;

StayOnCurrentNode:
        afficherCarte();

        printf ("Programme: ");
        afficher(seq);
        printf ("\e[%dC^^^\n", 10 + i * 5);
		
		printf("Stack: ");
		show_stack(stack);
        printf ("\n");

        if (debug) stop();
    }

    return CIBLERATEE;
}
