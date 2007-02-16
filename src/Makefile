# iimms2 - an XMMS2 client for wmii/dwm (using dmenu)
# Copyright (C) 2007  Sébastien Cevey

include ../config.mk

LIBDIRS = cmd_parser mario

SRC = iimms2.cpp dictfeed.cpp xmms2commands.cpp

OBJ = ${SRC:.cpp=.o}

all: iimms2
	@echo built iimms2

.cpp.o:
	@echo CC $<
	@${CXX} -c ${CXXFLAGS} $<

iimms2: libs ${OBJ}
	@echo LD $@
	${CXX} -o $@ ${OBJ} ${LDFLAGS}

libs:
	@for l in ${LIBDIRS}; do \
		(cd $$l; make) \
	done

clean:
	rm -f iimms2 *.o
	@for l in ${LIBDIRS}; do \
		(cd $$l; make clean) \
	done
