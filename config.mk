# Customize to fit your system

# paths
PREFIX = /usr/local
CONFPREFIX = ${PREFIX}/etc
MANPREFIX = ${PREFIX}/share/man

VERSION = 0.1

# includes and libs
XMMS2INCL = `pkg-config --cflags xmms2-client-cpp`
XMMS2LIBS = `pkg-config --libs xmms2-client-cpp`

LIBS = -L${PREFIX}/lib -L/usr/lib -L${XMMS2LIBS} -lxmmsclient++ \
	-Lmario -lmario -Lcmd_parser -lcmd_parser

CXXFLAGS = -O2 -Wall -I. -I${PREFIX}/include -I/usr/include ${XMMS2INCL} \
	-DVERSION=\"${VERSION}\" 
LDFLAGS = -O2 ${LIBS}

AR = ar cr
CXX = c++
RANLIB = ranlib
