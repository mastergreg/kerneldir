#!/bin/sh

current=`readlink linux`
orig=`readlink linux-orig`

if [ ! -e "$current" ]; then
    echo "Make sure your kernel source directory is present and create a link named 'linux' to it."
    echo "e.g. $ ln -s linux-2.6.37.4 linux"
    exit 1
fi

if [ ! -e "$orig" ]; then
    echo "Make sure the original kernel source directory is present and create a link named 'linux-orig' to it."
    echo "e.g. $ ln -s linux-2.6.37.4-orig linux-orig"
    exit 1
fi

mv -f curse.patch curse.patch.old

diff -uprN -X $current/Documentation/dontdiff $orig $current > curse.patch

