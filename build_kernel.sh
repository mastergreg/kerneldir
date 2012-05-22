#!/bin/bash
kerneldir=linux-2.6.37.4
if [ -z $1 ];
  then
	echo "You are safe from Mister Proper this time"
  else
	echo "Mister Proper is coming"
	make -C $kerneldir mrproper
	make -C $kerneldir mrproper ARCH=um

fi

make -C $kerneldir defconfig ARCH=um SUBARCH=$(uname -m)
make -C $kerneldir ARCH=um SUBARCH=$(uname -m)  CC=gcc-4.4 -j4

