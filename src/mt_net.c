#include <stdio.h>
#include <stdlib.h>

#include <mt_dtype.h>
#include <mt_net.h>
#include <mt_station.h>
#include <mt_line.h>

/**
 * Constructs a new net structure
 *
 * @param int stations_count	Number of stations this net will store
 * @param int lines_cont		Number of lines this net will store
 *
 * @return net 					The new net
 */
net *new_net(int stations_count, int lines_count) {
	int i;
	net *n = (net *) malloc(sizeof(net)); // memory allocation
	n->n_lines_created = 0; // no line has been created yet
	n->n_stations = stations_count; // dimensioning
	n->n_lines = lines_count; // dimensioning
	/* memory allocations for pointers to n_stations and pointers to n_lines */
	n->stations = (station **) calloc(stations_count, sizeof(station *));
	n->lines = (line **) calloc(lines_count, sizeof(line *));
	/* inits the fresh new pointers */
	for(i = 0; i < n->n_stations; i++) {
		n->stations[i] = NULL;
	}
	for(i = 0; i < n->n_lines; i++) {
		n->lines[i] = NULL;
	}
	return n;
}

/**
 * Creates the stations of a net and asigns ids to them
 *
 * @param net *n					The net to store the stations in
 * @param char *stations_names[]	The names of the stations
 */
void net_create_stations(net *n, char *stations_names[]) {
	int i;
	station *s;
	for(i = 0; i < n->n_stations; i++) {
		s = new_station(i, stations_names[i]);	// creates each station
		n->stations[i] = s;						// gives it and id
	}
}

/**
 * Creates a new line into net n
 *
 * @param net	*n				The holder net for the line
 * @param char	*line_name		The line dispay name
 * @param int	*stations_ids	The stations' ids to allocate, in proper order
 * @param int	stations_count	Number of stations to allocate
 * @param int 	length			Total line length
 *
 * @return line					The new line, NULL if there was not left space
 */
line *net_create_line(net *n, char *line_name,
		int *stations_ids, int stations_count, int length) {
	if(n->n_lines_created < n->n_lines) { // validate available space
		/* calls the line constructor */
		line *l = new_line(n, n->n_lines_created, line_name, stations_ids,
				stations_count, length);
		n->lines[n->n_lines_created++] = l; // registers the line created
		return l;
	}
	printf("ERROR: Too much lines for this net. Aborting!\n");
	return NULL;
}

/**
 * Obtains a station by id from net n
 *
 * @return station*	A pointer to the station or NULL if not found in n
 */
station *net_get_station(net *n, int id) {
	if(id >= n->n_stations || id < 0) {
		return NULL;
	}
	return n->stations[id];
}

/**
 * Obtains a line by id from net n
 *
 * @return line*	A pointer to the line or NULL if not found in n
 */
line *net_get_line(net *n, int id) {
	if(id >= n->n_lines || id < 0) {
		return NULL;
	}
	return n->lines[id];
}

/**
 * Prints a human friendly list of all lines in the net
 */
void net_print_lines(net *n) {
	int i;
	for(i = 0; i < n->n_lines; i++) {
		printf(" %02d - Linea %s\n", n->lines[i]->id, n->lines[i]->name);
	}
}
