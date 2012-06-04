#!/bin/sh

echo "creating big0..."
dd if=/dev/zero of=./big0 bs=1024k count=500
echo " "

#cursepie -a -N no_fs_cache
#cursepie -c -N no_fs_cache -P $$

echo "1st read..."
dd if=./big0 of=/dev/null bs=512k

echo "2st read..."
dd if=./big0 of=/dev/null bs=512k
#echo "disrupt and press enter..."
#read c

rm ./big0 
#cursepie -l -N no_fs_cache -P $$
#cursepie -d -N no_fs_cache
