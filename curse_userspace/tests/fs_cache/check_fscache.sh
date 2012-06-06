#!/bin/sh

echo "creating big0..."
dd if=/dev/zero of=./big0 bs=1024k count=200
echo " "

echo "creating big1..."
dd if=/dev/zero of=./big1 bs=1024k count=200
echo " "


echo "1st read..."
dd if=./big0 of=/dev/null bs=512k
echo " "

if [ x"$1" = x"curse" ];
then
	echo "Curse you!!"
	cursepie -a -N no_fs_cache
	cursepie -c -N no_fs_cache -P $$
fi

echo "Disruptive read..."
dd if=./big1 of=/dev/null bs=512k
echo " "

if [ x"$1" = x"curse" ];
then
	echo "Heal you!!"
	cursepie -l -N no_fs_cache -P $$
	cursepie -d -N no_fs_cache
fi

echo "2st read..."
dd if=./big0 of=/dev/null bs=512k
echo " "

echo "3st read..."
dd if=./big0 of=/dev/null bs=512k
echo " "


rm ./big0 
rm ./big1
