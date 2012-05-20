#!/bin/bash
cd linux-2.6.37.4
make mrproper
make mrproper ARCH=um
make defconfig ARCH=um SUBARCH=x86_64
make ARCH=um SUBARCH=x86_64 CC=gcc-4.4 -j6

