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
		r = activate(switches)
	elif '-d' in switches:
		r = deactivate(switches)
	elif '-c' in switches:
		r = cast(switches)
	elif '-l' in switches:
		r = lift(switches)
	elif '-L' in switches:
		r = listC(switches)
	elif '-t' in switches:
		r = check_tainted_proc(switches)
	elif '-s' in switches:
		r = check_curse_status(switches)
	elif '-h' in switches:
		r = showhelp()
	else:
		r = showhelp()
	exit(r)

if __name__=="__main__":
	main()
