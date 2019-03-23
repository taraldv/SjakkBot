PROG = sjakkBot
CC = g++
CPPFLAGS = -Wall -ggdb -std=c++11
DEPENDFLAGS += -std=c++11

OBJS = benchmark.o bitbase.o bitboard.o endgame.o evaluate.o main.o \
	material.o misc.o movegen.o movepick.o pawns.o position.o psqt.o \
	search.o thread.o timeman.o tt.o uci.o ucioption.o syzygy/tbprobe.o

all: $(PROG) .depend

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS)

.depend:
	-@$(CC) $(DEPENDFLAGS) -MM $(OBJS:.o=.cpp) > $@ 2> /dev/null

-include .depend

clean:
	rm -f *stackdump $(PROG) main.o uci.o search.o