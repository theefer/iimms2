# iimms2 - an XMMS2 client for wmii/dwm (using dmenu)
# Copyright (C) 2007  Sébastien Cevey

include config.mk

SUBDIRS = src

BIN = cmd/iimms2

APP = iimms2

all:
	@echo iimms2 build options:
	@echo "LIBS     = ${LIBS}"
	@echo "CXXFLAGS = ${CXXFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CXX      = ${CXX}"
	@echo
	@for i in ${SUBDIRS}; do \
		(cd $$i; make) \
	done

dist: clean
	mkdir -p ${APP}-${VERSION}
	cp -R Makefile README COPYING config.mk ${SUBDIRS} ${APP}-${VERSION}
	tar -cf ${APP}-${VERSION}.tar ${APP}-${VERSION}
	gzip ${APP}-${VERSION}.tar
	rm -rf ${APP}-${VERSION}

clean:
	for i in ${SUBDIRS}; do \
		(cd $$i; make clean); \
	done
	rm -rf ${APP}-${VERSION}*

install: all
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f ${BIN} ${DESTDIR}${PREFIX}/bin
	@for i in ${BIN}; do \
		chmod 755 ${DESTDIR}${PREFIX}/bin/`basename $$i`; \
	done
	@echo installed executable files to ${DESTDIR}${PREFIX}/bin

uninstall:
	for i in ${BIN}; do \
		rm -f ${DESTDIR}${PREFIX}/bin/`basename $$i`; \
	done
