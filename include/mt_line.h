#ifndef __MT_LINE_H__
#define __MT_LINE_H__

line *new_line(net *n, int id, char *name, int stations_ids[], int
		stations_count, int length);
void line_print(line *l);
station *line_get_station(line *l, int id);

#endif
