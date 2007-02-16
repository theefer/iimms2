# mario - a C++ lib for using pipes, feeds, commands and stuff
# Copyright (C) 2007  Sébastien Cevey

include ../../config.mk

CXXFLAGS += -I ..

SRC = mario.cpp

OBJ = ${SRC:.cpp=.o}

all: libmario.a
	@echo built libmario

.cpp.o:
	@echo CC $<
	@${CXX} -c ${CXXFLAGS} $<

libmario.a: ${OBJ}
	@echo AR $@
	@${AR} $@ ${OBJ}
	@${RANLIB} $@

clean:
	rm -f libmario.a *.o
