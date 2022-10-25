#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"


/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

bool silent_mode = false;


static cellule_t* new_cell(char c) {
	cellule_t* rv = calloc(1, sizeof(cellule_t));
	rv->cmd = c;
	return rv;
}


static int valid_char(char c) {
	return c != ' ' && c != '\n';
}


#define NEXT(c) c = c->suivant
void conversion(char* text, sequence_t* seq) {
	assert(text && seq);
	if (!*text) return;  // if string is empty, do nothing

	cellule_t* cell = new_cell(*text);
	seq->tete = cell;
	text++;

	while (*text) {
		if (valid_char(*text)) {
			cell->suivant = new_cell(*text);
			NEXT(cell);
		}
		text++;
	}
}


void afficher(sequence_t* seq) {
    assert (seq);
	cellule_t* cell = seq->tete;
	while (cell) {
		printf("%c -> ", cell->cmd);
		NEXT(cell);
	}
	printf("NULL\n");
}


void clear_sequence_contents(sequence_t* seq) {
	assert(seq);
	cellule_t* current_node = seq->tete;
	cellule_t* next_node;

	while (current_node) {
		next_node = current_node->suivant;
		free(current_node);
		current_node = next_node;
	}
}
