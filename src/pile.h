#ifndef PILE_H
#define PILE_H

typedef struct stack_node {
	int val;
	struct sequence* sous_sequence;
	struct stack_node* next;
} StackNode;

typedef struct {
	StackNode* head;
} Stack;

void push(Stack*, int);

int pop(Stack*);

void push_seq(Stack*, struct sequence*);

struct sequence* pop_seq(Stack*);

void calcul(Stack*, int(*fn)(int, int));

void show_stack(Stack*);

void clear_stack(Stack*);

#endif
