#include <stdio.h>
#include <stdlib.h>

#include <mt_dtype.h>
#include <mt_station.h>
#include <mt_link.h>

/**
 * Constructs a new station structure
 */
station *new_station(int id, char *name) {
	station *s = (station *) malloc(sizeof(station)); // memory allocation
	/* structure construction */
	s->name = name;
	s->id = id;
	s->links = NULL;
	s->graph_previous = NULL;
	s->graph_distance = MT_STATION_INFINITY;
	s->graph_visited = 0;
	s->list_next = NULL;
	s->stack_next = NULL;
	return s;
}

/**
 * Appends a new link to station's links list
 */
void station_add_link(station *s, link *l) {
	link *hl;						// helper link
	if(s->links == NULL) {
		s->links = l;
	}
	else {
		hl = s->links;		
		while(hl->next != NULL) {
			hl = hl->next;
		}
		hl->next = l;
	}
}

/**
 * Buils a double link from s to to and from to to s
 */
link *station_link_to(station *s, station *to, int distance) {
	link *hl = s->links;				// helper link
	while(hl) {
		if(hl->to == to) {
			return hl; 					// there is a link already
		}
		hl = hl->next;
	}
	hl = new_link(s, to, distance);
	hl = new_link(to, s, distance);		// the link is reciprocal
	return hl;
}

