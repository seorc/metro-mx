#ifndef __MT_STATION_LIST_H__
#define __MT_STATION_LIST_H__

#define SORT_DES 1 
#define SORT_OFF 2
#define SORT_ASC 3

station_list *new_station_list(char sort);
station *station_list_first(station_list *sl);
void station_list_add(station_list *list, station *s);
void station_list_print(station_list *sl);

#endif
