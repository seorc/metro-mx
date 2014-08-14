#include <stdio.h>
#include <stdlib.h>

#include <mt_dtype.h>

/**
 * Constructs a new link
 */
link *new_link(station *s, station *to, int length) {
	link *l = (link *) malloc(sizeof(link)); // space allocation
	l->next = NULL; // statioins administrate its owned links whit this
	l->to = to; // our target
	l->length = length; // distance between s and to
	station_add_link(s, l); // chain this link into the station
	return l;
}
