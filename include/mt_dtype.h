#ifndef __MT_DTYPE_H__
#define __MT_DTYPE_H__

/* counts the number of elements into an array */
#define COUNT(arr) (sizeof arr / sizeof arr[0])

/* TYPE DEFINITIONS */
typedef struct _line line;
typedef struct _link link;
typedef struct _net net;
typedef struct _station station;
typedef struct _station_list station_list;
typedef struct _station_stack station_stack;

/**
 * Represents a network of metro lines
 * It's the actual store for all the lines an stations
 */
struct _net {
	int n_lines;				// number of lines in the net
	int n_lines_created;		// number of lines already created
								// must not exceed n_lines
	int n_stations;				// number of station in the net
	station **stations;			// store for the actual stations
	line **lines;				// store for the actual lines
};

/**
 * Represents a subgroup of a net
 * Cointains an array of pointers to the corresponding stations existing
 * in a net. This line must be part of that net
 */
struct _line {
	char *name;					// human friendly representation
	int id;						// key to identify each individual line
	int n_stations;				// number of stations in the line
	station **stations;			// store for the actual stations
};

/**
 * Monodirectional link to a station
 * Each station maintains a set of links to all other stations the are
 * connected with. This structure represents the distance between stations.
 * The autoreferenced pointer it has allows to create lists of links, which
 * is the way stations store their sets of links
 */
struct _link {
	station *to;				// station the link points to
	int length; 				// distance in meters
	link *next;					// to chain links as lists
};

/**
 * Represents a station
 * It has special variables to interact with graphs, lists and stacks. These
 * members shouldn't be manipulated by other routines; that's why their names
 * are prefixed with the type of data structure associated to them
 */
struct _station {
	char *name;					// the display name of the structure
	int id;						// in unique id for the structure
	link *links;				// station's list of links
	/* graph support */
	int graph_visited;			// if the station has been visited in a search
	int graph_distance; 		// to store distances on runtime
	station *graph_previous;	// to store previous visited nodes on runtime
	/* list suport */
	station *list_next;			// to use with singlelists
	station *stack_next;		// to use with stacks
};

/**
 * Helper structur to suppor stations in lists
 */
struct _station_list {
	char sort;					// flag to define the list's sorting behaviour
	station *first;				// pointer to the firs element of the list
};

/**
 * Helper structur to suppor stations in staks
 */
struct _station_stack {
	station *top;				// the top element of the list
};

#endif
