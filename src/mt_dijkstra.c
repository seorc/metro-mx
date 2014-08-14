#include <stdio.h>

#include <mt_dtype.h>
#include <mt_dijkstra.h>
#include <mt_net.h>
#include <mt_station.h>
#include <mt_station_list.h>
#include <mt_station_stack.h>

/**
 * Calculates all sorthest paths from source to any node
 *
 * Implements Dijkstra's Algorithm to make the resolution
 * 
 * @param net 		*n 		The net representing the graph to search in
 * @param station 	*source The station to starto the algorithm from
 */
void dijk_make(net *n, station *source) {
	int i;				// for generic porpouses
	station *hs;		// helper stations
	link *hl;			// helper link

	station_list *stl = new_station_list(SORT_ASC); // psedo priority queue
	
	/* inits all values to execuete the algorithm */
	for(i = 0; i < n->n_stations; i++) {
		hs = n->stations[i];
		hs->graph_distance = MT_STATION_INFINITY; // all stations are too far
		hs->graph_previous = NULL; // all previous to null; just starting
		hs->graph_visited = 0; // no station has been visited
	}

	source->graph_distance = 0; // source station is very near
	station_list_add(stl, source); // source is our first option to go
	
	while(hs = station_list_first(stl)) {
		//if(hs->graph_visited) continue;
		hl = hs->links; // to search all connections from current station
		//station_list_print(stl);
		while(hl) {
			if(hl->to->graph_visited) {
				hl = hl->next;	// don't visit an already visited station
				continue;
			}
			/* this one is a bit ofuscated:
			 * tests if current distance to current candidate linked station is
			 * shorter than other distances calculated from other sources
			 * previously
			 */
			if(hs->graph_distance + hl->length < hl->to->graph_distance
					|| hl->to->graph_distance == MT_STATION_INFINITY) {
				/* if so, defines this distance into the station */
				hl->to->graph_distance = hs->graph_distance + hl->length;
				/* sets current station as previous for candidate station */
				hl->to->graph_previous = hs;
				/* adds the candidate station to the pseudo priority queue */
				station_list_add(stl, hl->to);
			}
			hl = hl->next; // lets go with the next linked station
		}
		hs->graph_visited = 1;
	}
}

/**
 * Prints the route to arrive to dest
 * 
 * You must run {@link dijk_make()} first to set the source
 *
 * @param station *dest The station to arrive from source station
 */
void dijk_print_path(station *dest) {
	/* as we search from dest to origin, we use a stack to reverse the route
	 * order */
	station_stack *sstack = new_station_stack();
	int dist; // helper var
	while(dest) {
		// loading the stack
		station_stack_push(sstack, dest);
		dest = dest->graph_previous;
	}
	printf("\n");
	while(dest = station_stack_pop(sstack)) {
		// obaining items and printing them
		printf("  => %s\n", dest->name);
		dist = dest->graph_distance; // store always the last distance
	}
	printf("\n");
	printf("  Distancia aproximada a recorrer: %.1f Km\n",
		(double) dist/1000.0);
	printf("\n");
}
