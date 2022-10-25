#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pile.h"

void push(Stack* stack, int x) {
	assert(stack);
	StackNode* old_head = stack->head;
	StackNode* new_head = malloc(sizeof(StackNode));

	new_head->val = x;
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
		printf("%d -> ", current_node->val);
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
		free(current_node);
		current_node = next_node;
	}

	free(stack);
}
