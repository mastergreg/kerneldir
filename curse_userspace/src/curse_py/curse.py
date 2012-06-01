#!/usr/bin/env python
# -*- coding: utf-8


from curses import *
from getopt import gnu_getopt, GetoptError

def parse_args():
	try:
		switches, args = gnu_getopt(argv[1:],'adcli:p:N:P:Ltsh?')
	except GetoptError:
		showhelp()
		exit(1)
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
	elif '-i' in switches:
		r = inheritance(switches)
	elif '-p' in switches:
		r = permissions(switches)
	elif '-h' in switches:
		r = showhelp()
	else:
		r = showhelp()
	print "Return status {0}".format(r)
	exit(r)

if __name__=="__main__":
	main()
