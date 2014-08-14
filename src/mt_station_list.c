#include <stdio.h>
#include <stdlib.h>

#include <mt_dtype.h>
#include <mt_station_list.h>

/**
 * Station_list doesn't behaves exactly as a list. It has tow differences:
 *
 *  - It removes any duplicates of any elements you insert,
 *    before inserting it
 *  - It can keep its elements sorted, to permit it act like a priority queue
 */

/**
 * Constructs a new station_list
 *
 * @param char sort		Tells if this list must be kept sorted
 *
 * @return station		The new station
 */
station_list *new_station_list(char sort) {
	station_list *sl = (station_list *) malloc(sizeof(station_list));
	sl->sort = sort;
	sl->first = NULL;
	return sl;
}

/**
 * Adds a station to list
 */
void station_list_add(station_list *list, station *s) {
	station *hs, *hs_prev; // helper stations
	int insert;
	/* to start iterating */
	hs = list->first;
	hs_prev = NULL;
	/* first, remove any duplicate from this list */
	while(hs) {
		if(hs == s) {
			/* it only will be posbible when whe are at the list's root
			 * (check next if block) */
			list->first = hs->list_next;
		}
		if(hs->list_next == s) {
			hs_prev = hs->list_next; // remove any duplicates
			hs->list_next = hs->list_next->list_next;
			hs_prev->list_next = NULL; // unset removed station's binding
		}
		hs = hs->list_next; // go on
	}
	if(list->first == NULL || list->sort == SORT_OFF) {
		/* if we are just in the root, or not in sorting mode, there is
		 * not too much to do */
		s->list_next = list->first;
		list->first = s;
		return;
	}
	/* to start iterating */
	hs = list->first;
	hs_prev = NULL;
	/* for sortin aware insertion */
	while(hs) {
		/* decides if s must be inserted in current position */
		insert =
			(list->sort == SORT_DES && s->graph_distance > hs->graph_distance)
			||
			(list->sort == SORT_ASC && s->graph_distance < hs->graph_distance);

		if(insert) {
			if(hs == list->first) {
				list->first = s;
			}
			else {
				hs_prev->list_next = s;
			}
			s->list_next = hs;
			return;
		}
		else if(hs->list_next == NULL) {
			hs->list_next = s;
			return;
		}
		hs_prev = hs;
		hs = hs->list_next;
	}
}

/**
 * Extracts and removes the first element in the list
 */
station *station_list_first(station_list *sl) {
	station *hs; // helper station
	hs = sl->first;
	if(hs == NULL) {
		return NULL;
	}
	sl->first = hs->list_next;
	hs->list_next = NULL; // unset extracted station binding
	return hs;
}

/**
 * Prints a human friendly, quite ugly representation of list
 */
void station_list_print(station_list *sl) {
	station *hs; // helper station
	hs = sl->first;
	printf("==== station_list[]: ");
	while(hs) {
		printf("%03d %s (%d) -> ", hs->id, hs->name, hs->graph_distance);
		hs = hs->list_next;
	}
	printf(" ºººº\n");
}
