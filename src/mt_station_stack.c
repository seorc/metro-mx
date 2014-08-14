#include <stdio.h>
#include <stdlib.h>

#include <mt_dtype.h>
#include <mt_station_stack.h>
#include <mt_station.h>

/**
 * Constructs a new stack
 */
station_stack *new_station_stack() {
	station_stack *ss = (station_stack *) malloc(sizeof(station_stack));
	ss->top = NULL;
	return ss;
}

/**
 * Checks stack's emtpy status
 */
int station_stack_empty(station_stack *stack) {
	return stack->top == NULL;
}

/**
 * Inserts a new element in stack
 */
void station_stack_push(station_stack *stack, station *s) {
	s->stack_next = NULL;
	if(!station_stack_empty(stack)) {
		s->stack_next = stack->top;
	}
	stack->top = s;
}

/**
 *	Removes the last added element from stack
 */
station *station_stack_pop(station_stack *stack) {
	if(!station_stack_empty(stack)) {
		station *s = stack->top;
		stack->top = s->stack_next;
		s->stack_next = NULL; // clean binding
		return s;
	}
	return NULL;
}
