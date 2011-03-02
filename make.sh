#!/bin/sh

if [ $# != 1 ]; then
    echo "Usage: ./make.sh <debug | release>"
    exit
fi
MODE=$1

echo "Configuration: $1."
make distclean
qmake "CONFIG=$MODE" -r
make clean
