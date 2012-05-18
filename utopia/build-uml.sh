#!/bin/sh

if [ ! -e linux/.config ]; then
    make -C linux ARCH=um SUBARCH=i386 defconfig
fi

make -C linux ARCH=um SUBARCH=i386 -j2

