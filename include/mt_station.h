#ifndef __MT_STATION_H__
#define __MT_STATION_H__

#define MT_STATION_INFINITY -1

station *new_station(int id, char *name);
void station_add_link(station *s, link *l);
link *station_link_to(station *s, station *to, int distance);

#endif
