# Customize to fit your system

# paths
DMENU_PATH = /home/seb/Build/dmenu.hg/dmenu

PREFIX = /usr/local
CONFPREFIX = ${PREFIX}/etc
MANPREFIX = ${PREFIX}/share/man

# dist infos
APP_NAME = iimms2
VERSION = 0.1

# includes and libs
XMMS2INCL = `pkg-config --cflags xmms2-client-cpp`
XMMS2LIBS = `pkg-config --libs xmms2-client-cpp`

LIBS = -L${PREFIX}/lib -L/usr/lib -L${XMMS2LIBS} -lxmmsclient++ \
	-Lmario -lmario -Lcmd_parser -lcmd_parser

CXXFLAGS = -O2 -Wall -I. -I${PREFIX}/include -I/usr/include ${XMMS2INCL} \
	-DVERSION=\"${VERSION}\" -DDMENU_PATH=\"${DMENU_PATH}\" \
	-DCLIENT_NAME=\"${APP_NAME}\"
LDFLAGS = -O2 ${LIBS}

AR = ar cr
CXX = c++
RANLIB = ranlib
