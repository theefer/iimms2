#!/bin/sh

if [ ! -d ext/ ]
then
    echo "Create directory ext/"
    mkdir ext
fi

if [ ! -d ext/nyello.git/ ]
then
    echo -n "Pulling nyello's sources... "
    git-clone git://exodus.xmms.se/xmms2/nyello.git/ ext/nyello.git > /dev/null 2>&1
    echo "done!"

    echo -n "Configuring nyello's sources... "
    (cd ext/nyello.git/; ./configure) > /dev/null 2>&1
    echo "done!"
else
    echo -n "Updating nyello's sources... "
    (cd ext/nyello.git/; git-pull) > /dev/null 2>&1
    echo "done!"
fi

if [ ! -h src/cmd_parser ]
then
    echo "Symlink cmd_parser"
    (cd src; ln -s ../ext/nyello.git/src/cmd_parser cmd_parser) > /dev/null 2>&1
fi

echo "cmd_parser ready!"