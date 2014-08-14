IDIR=include
CC=gcc
CFLAGS=-g -I$(IDIR)

SDIR=src
ODIR=$(SDIR)/obj

LIBS=

_DEPS=mt_dtype.h mt_line.h mt_link.h mt_net.h mt_station.h mt_dijkstra.h mt_station_list.h mt_station_stack.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=metro.o mt_line.o mt_link.o mt_net.o mt_station.o mt_dijkstra.o mt_station_list.o mt_station_stack.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

metro: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(IDIR)/*~
