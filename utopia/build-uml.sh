#!/bin/sh

if [ ! -e linux/.config ]; then
    make -C linux ARCH=um SUBARCH=x86_64 defconfig
fi

make -C linux ARCH=um SUBARCH=x86_64  -j5

