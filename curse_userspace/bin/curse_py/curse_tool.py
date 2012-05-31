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

def parseInt(sth):
	sth = map(ord, sth)
	s = 0
	for i,j in enumerate(sth):
		s += 256**i*j
	return s

class curse_list_entry(Structure):
	_buf_size_ = 24
	_pack_ = 1
	_fields_ = [('curse_name',c_char*24), ('curse_id', c_ulonglong)]
	def __init__(self,st):
		self.curse_name = st[:self._buf_size_]
		self.curse_id = parseInt(st[self._buf_size_:])

	def __repr__(self):
		return "{0}: {1:#08x}".format(self.curse_name,self.curse_id)

		




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


def parse_cbuf(sth, ln):
	a = []
	for j in range(ln):
		i = j*32
		a.append(curse_list_entry(sth[i:i+32]))
	return a



def listC(switches):
	c_no = curse(GET_CURSE_NO, None, 0, 0, None)
	size = c_no*sizeof(curse_list_entry)
	c_buf = create_string_buffer(size)
	dome = curse_list_entry*c_no
	curse(LIST_ALL, None, 0, 0, c_buf)
	return parse_cbuf(c_buf, c_no)

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
		for el in l:
			print el
	elif '-h' in switches:
		showhelp()
	else:
		showhelp()

if __name__=="__main__":
	main()
