#ifndef __MT_NET_H__
#define __MT_NET_H__

net *new_net(int stations_count, int lines_count);
void net_create_stations(net *n, char *stations_names[]);
void net_print_lines(net* n);
station *net_get_station(net *n, int id);
line *net_get_line(net *n, int id);
line *net_create_line(net *n, char *line_name,
		int *stations_ids, int stations_count, int length);

#endif
