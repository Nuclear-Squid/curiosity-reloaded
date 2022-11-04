#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "listes.h"
#include "pile.h"

void push(Stack* stack, int x) {
	assert(stack);
	StackNode* old_head = stack->head;
	StackNode* new_head = malloc(sizeof(StackNode));

	new_head->val = x;
	new_head->sous_sequence = NULL;
	new_head->next = old_head;
	stack->head = new_head;
}

int pop(Stack* stack) {
	assert(stack);
	assert(stack->head);

	StackNode* old_head = stack->head;
	StackNode* new_head = old_head->next;

	int rv = old_head->val;

	free(old_head);
	stack->head = new_head;
	return rv;
}

void push_seq(Stack* stack, sequence_t* seq) {
	assert(stack);
	StackNode* old_head = stack->head;
	StackNode* new_head = malloc(sizeof(StackNode));

	new_head->val = 0;
	new_head->sous_sequence = seq;
	new_head->next = old_head;
	stack->head = new_head;
}

sequence_t* pop_seq(Stack* stack) {
	assert(stack && stack->head);

	StackNode* old_head = stack->head;
	StackNode* new_head = old_head->next;

	sequence_t* rv = old_head->sous_sequence;

	free(old_head);
	stack->head = new_head;
	return rv;
}

void calcul(Stack* stack, int(*fn)(int, int)) {
	assert(stack);
	int buff1 = pop(stack);
	int buff2 = pop(stack);
	push(stack, fn(buff2, buff1));
}

#define NEXT(c) c = c->next
void show_stack(Stack* stack) {
	assert(stack);
	StackNode* current_node = stack->head;

	while (current_node) {
		if (current_node->sous_sequence) {
			afficher(current_node->sous_sequence);
		} else {
			printf("%d -> ", current_node->val);
		}
		NEXT(current_node);
	}
	printf("NULL\n");
}

void clear_stack(Stack* stack) {
	assert(stack);
	StackNode* current_node = stack->head;
	StackNode* next_node;

	while (current_node) {
		next_node = current_node->next;
		/* if (current_node->sous_sequence) { */
		/* 	clear_sequence_contents(current_node->sous_sequence); */
		/* 	free(current_node->sous_sequence); */
		/* } */
		free(current_node);
		current_node = next_node;
	}

	free(stack);
}

void swap_head(Stack* stack) {
	assert(stack);
	StackNode* tmp_head = stack->head;
	StackNode* tmp_head_next = stack->head->next;

	stack->head = tmp_head_next;
	tmp_head->next = tmp_head_next->next;
	stack->head->next = tmp_head;
}

void clone_head(Stack* stack) {
	assert(stack);
	assert(stack->head);
	StackNode* new_head = malloc(sizeof(StackNode));

	new_head->val           = stack->head->val;
	new_head->sous_sequence = stack->head->sous_sequence;
	new_head->next          = stack->head;

	stack->head = new_head;
}


#define VALID_NODE(node) \
	if (!node) {\
		eprintf("Stack node out of range\n");\
		exit(1);\
	}
void rotation(Stack* stack, int step, int n_nodes) {
	assert(stack);

	// If true, output is the same as input, so do nothing.
	// (modulo is safe since `||` is a shortcut operator)
	if (n_nodes == 0 || n_nodes == 1 || step % n_nodes == 0) return;

	step = n_nodes - (step % n_nodes);

	StackNode* current_node = stack->head;
	for (int i = 0; i < step - 1; i++) {
		VALID_NODE(current_node);
		current_node = current_node->next;
	}
	StackNode* new_tail_segment = current_node;
	StackNode* new_head = new_tail_segment->next;

	for (int i = 0; i < n_nodes - step; i++) {
		VALID_NODE(current_node);
		current_node = current_node->next;
	}
	StackNode* old_tail_segment = current_node;
	StackNode* first_unchanged_node = current_node->next;

	old_tail_segment->next = stack->head;
	new_tail_segment->next = first_unchanged_node;
	stack->head = new_head;
}

void inverse(Stack* stack) {
	assert(stack);

	// if there is 0 or 1 element in the stack, do nothing
	if (!stack->head) return;
	if (!stack->head->next) return;

	StackNode* previous_node = NULL;
	StackNode* current_node = stack->head;
	StackNode* next_node = stack->head->next;

	do {
		current_node->next = previous_node;
		previous_node = current_node;
		current_node = next_node;
		next_node = next_node->next;
	} while (next_node);

	current_node->next = previous_node;
	stack->head = current_node;
}
