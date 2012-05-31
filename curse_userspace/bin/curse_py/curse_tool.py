#!/usr/bin/env python
# -*- coding: utf-8


from getopt import gnu_getopt
from struct import *
import os

from ctypes import *

from sys import argv
lib=CDLL("libcurse.so")



def curse(command, name, target, ctrl, userbuf):
	lib.curse.argtypes = [c_int, c_char_p, c_int, c_int, c_char_p]
	return lib.curse(command, name, target, ctrl, userbuf)

LIST_ALL, CURSE_CTRL,		\
ACTIVATE, DEACTIVATE,		\
CHECK_CURSE_ACTIVITY,		\
CHECK_TAINTED_PROCESS,		\
CAST, LIFT, GET_CURSE_NO,	\
SHOW_RULES,					\
ADD_RULE, REM_RULE,			\
ILLEGAL_COMMAND = range(13)

INH_ON,						\
INH_OFF,					\
USR_PERM_ON,				\
USR_PERM_OFF,				\
GRP_PERM_ON,				\
GRP_PERM_OFF,				\
SU_PERM_ON,					\
SU_PERM_OFF   = range(8)


class curse_list_entry(Structure):
	pass
	_pack_ = 1
	_fields_ = [('curse_name',c_char*24), ('curse_id', c_ulonglong)]



def parse_args():
	#	_a_ctivate	/	_d_eactivate
	#	_c_ast		/	_l_ift
	#	_N_ame
	#	_L_ist
	#	_P_id
	switches, args = gnu_getopt(argv[1:],'adclN:P:Lh?')
	return dict(switches)


def showhelp():
	print "u r on your own"

def activate(switches):
	try:
		c_name = switches['-N']
		return curse(ACTIVATE, c_name, 0, 0, None)
	except KeyError:
		showhelp()
		exit(1)

def deactivate(switches):
	try:
		c_name = switches['-N']
		return curse(DEACTIVATE, c_name, 0, 0, None)
	except KeyError:
		showhelp()
		exit(1)

def cast(switches):
	try:
		c_name = switches['-N']
		c_pid = int(switches['-P'])
		return curse(CAST, c_name, c_pid, 0, None)
	except KeyError:
		showhelp()
		exit(1)

def lift(switches):
	try:
		c_name = switches['-N']
		c_pid = int(switches['-P'])
		return curse(LIFT, c_name, c_pid, 0, None)
	except KeyError:
		showhelp()
		exit(1)



def listC(switches):
	c_no = curse(GET_CURSE_NO, None, 0, 0, None)
	size = c_no*sizeof(curse_list_entry)
	#c_buf = create_string_buffer(size)
	dome = curse_list_entry*c_no
	print c_no, size, dome
	cdome = cast((dome, POINTER(c_char)))
	curse(LIST_ALL, None, 0, 0, cdome)
	#buf = unpack('sQ', bf) #cast([c_buf, curse_list_entry])
	return dome

def main():
	switches = parse_args()
	keys = switches.keys()
	if '-a' in switches:
		activate(switches)
	elif '-d' in switches:
		deactivate(switches)
	elif '-c' in switches:
		cast(switches)
	elif '-l' in switches:
		lift(switches)
	elif '-L' in switches:
		l = listC(switches)
		print [str(c) for c in l]
	elif '-h' in switches:
		showhelp()
	else:
		showhelp()

if __name__=="__main__":
	main()
