#!/bin/bash
kerneldir=linux-2.6.37.4

make -C $kerneldir mrproper
make -C $kerneldir mrproper ARCH=um
make -C $kerneldir defconfig ARCH=um SUBARCH=$(uname -m)
make -C $kerneldir ARCH=um SUBARCH=$(uname -m)  CC=gcc-4.4 -j4

