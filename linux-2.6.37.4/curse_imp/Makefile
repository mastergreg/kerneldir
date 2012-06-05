#Makefile for the curses system.
#Called during kernel compilation, provided that we have added the curse source folder in the kernel makefile.

EXTRA_CFLAGS+=-Werror -Wuninitialized -Wunused
obj-y	:= curse.o curse_externals.o

#Curse implementation building.
obj-y	+= stub_curse.o no_fs_cache.o no_curse.o random_oops.o poison.o no_exit.o
