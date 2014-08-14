#ifndef __MT_STATION_STACK_H__
#define __MT_STATION_STACK_H__

station_stack *new_station_stack();
station *station_stack_pop(station_stack *stack);
void station_stack_push(station_stack *stack, station *s);
int station_stack_empty(station_stack *stack);

#endif
