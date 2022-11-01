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
	return c != ' ' && c != '\n' && c != '\r';
}


#define NEXT(c) c = c->suivant
void conversion(char* text, sequence_t* seq) {
	assert(text && seq);
	static int i = 0;

	// if string or code block is empty, do nothing
	if (text[i] == 0 || text[i] == '}') return;

	cellule_t* cell = new_cell(text[i]);
	seq->tete = cell;

	while (text[i + 1]) {
		i++;

		if (text[i] == '}') return;

		if (valid_char(text[i])) {
			cell->suivant = new_cell(text[i]);
			NEXT(cell);

			if (text[i] == '{') {
				i++;
				cell->sous_sequence = calloc(1, sizeof(sequence_t));
				conversion(text, cell->sous_sequence);
			}
		}
	}

	// If we got here, then it's the end of the string.
	i = 0;
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
		if (current_node->sous_sequence) {
			clear_sequence_contents(current_node->sous_sequence);
			free(current_node->sous_sequence);
		}
		free(current_node);
		current_node = next_node;
	}
}
