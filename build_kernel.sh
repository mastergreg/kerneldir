#!/bin/bash

HOST=$(uname -m)
if [ $HOST == i686 ]
then
	HOST='i386'
fi

kerneldir=`dirname $0`/linux-2.6.37.4
if [ -z $1 ];
  then
	echo "You are safe from Mister Proper this time"
  else
	echo "Mister Proper is coming"
	make -C $kerneldir mrproper
	make -C $kerneldir mrproper ARCH=um

fi

if [ ! -f $kerneldir/.config ]
  then
	make -C $kerneldir defconfig ARCH=um SUBARCH=$HOST
  else
	echo Using old config
fi
make -C $kerneldir ARCH=um SUBARCH=$HOST  CC=gcc -j5

