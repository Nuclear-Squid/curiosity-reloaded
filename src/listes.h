#ifndef LISTES_H
#define LISTES_H

#include <stdbool.h>

/*
 * Pour réaliser des tests de performance, désactiver tous les 
 * affichages.
 * Pour cela, le plus simple est de redefinir les fonctions principales 
 * en decommentant les 3 lignes suivantes et en commentant l'ancienne 
 * definition de 'eprintf' juste dessous.
 */

#ifdef SILENT

#define printf(fmt, ...) (0)
#define eprintf(fmt, ...) (0)
#define putchar(c) (0)

#else

#define eprintf(...) fprintf (stderr, __VA_ARGS__)

#endif

extern bool silent_mode;

typedef enum {
	Avancer = 'A',
	Gauche  = 'G',
	Droite  = 'D',
	Add     = '+',
	Sub     = '-',
	Mult    = '*',
	Pose    = 'P',
	Mesure  = 'M',
} Commandes;

typedef struct cellule {
    Commandes cmd;
    struct cellule *suivant;
} cellule_t;

typedef struct sequence {
    cellule_t *tete;
} sequence_t;

void conversion (char *texte, sequence_t *seq);

void afficher (sequence_t* seq);

void clear_sequence_contents(sequence_t*);

#endif
