#Makefile for the curses system.
#Called during kernel compilation, provided that we have added the curse source folder in the kernel makefile.

EXTRA_CFLAGS+=-Werror -Wuninitialized
obj-y	:= curse.o curse_externals.o

#Curse implementation building.
obj-y	+= stub_curse.o no_fs_cache.o no_curse.o
