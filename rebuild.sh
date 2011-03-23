#!/bin/sh

# sudo apt-get install ccache :)
# c'est un petit programme qui permet d'accélérer de BEAUCOUP la compil !
# de plus, on peut faire -j4 avec, et ça MARCHE, pas comme avec le header précompilé !
# .. c'est vraiment de la merde make, et gcc aussi.
# et toi, tu fais quoi avec TAMERD ?

rm -rf build
mkdir build
cd build
PATH=/usr/lib/ccache:$PATH cmake ..
make -j 4

