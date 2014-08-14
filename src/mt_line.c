#include <stdio.h>
#include <stdlib.h>

#include <mt_dtype.h>
#include <mt_line.h>
#include <mt_station.h>

/**
 * Constructs a new line structure
 */
line *new_line(net *n, int id, char *name,
		int stations_ids[], int stations_count, int length) {
	int i;
	station *hs; // helper station
	int estimated_length;  // estimated inter-station distance (more below)
	line *l = (line *) malloc(sizeof(line)); // memory allocaion
	/* structure construction */
	l->n_stations = stations_count;
	l->name = name;
	/* allocates space necesary to maintain pointers to all its stations */
	l->stations = (station **) calloc(stations_count, sizeof(station *));
	l->id = id; // unique line identifier
	/* we only know te line total lenght, so we divide it by n_stations */
	estimated_length = length / l->n_stations;
	for(i = 0, hs = NULL; i < l->n_stations; i++) {
		/* setting each pointer to its respective station */
		l->stations[i] = n->stations[stations_ids[i]];
		if(hs) { // won't be executed in the first iteration
			/* create corresponging links between stations
			 * generates two links: one from a to b, the oter from b to a,
			 * each one with the same length */
			station_link_to(hs, l->stations[i], estimated_length);
		}
		/* we need to remember the previous station to create links */
		hs = l->stations[i];
	}
	return l;
}

/**
 * Prints a human friendly prepresentation of line
 */
void line_print(line *l) {
	int i;
	printf("L I N E A   %s\n", l->name);
	printf("========================\n", l->name);
	for(i = 0; i < l->n_stations; i++) {
		printf(" %02d - %s\n", i, l->stations[i]->name);
	}
}

/**
 * Returns the station within l with the specified id
 */
station *line_get_station(line *l, int id) {
	if(id >= l->n_stations || id < 0) {
		return NULL;
	}
	return l->stations[id];
}
