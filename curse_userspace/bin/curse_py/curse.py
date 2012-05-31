#!/usr/bin/env python
# -*- coding: utf-8


from curses import *
from getopt import gnu_getopt

def parse_args():
	switches, args = gnu_getopt(argv[1:],'adclN:P:Ltsh?')
	return dict(switches)



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
	elif '-t' in switches:
		check_tainted_proc(switches)
	elif '-s' in switches:
		check_curse_status(switches)
	elif '-h' in switches:
		showhelp()
	else:
		showhelp()

if __name__=="__main__":
	main()
