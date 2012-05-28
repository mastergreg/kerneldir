#!/usr/bin/env python
# -*- coding: utf-8
#
#* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
# File Name : curse.py
# Creation Date : 22-05-2012
# Last Modified : Tue 22 May 2012 05:00:04 PM EEST
# Created By : Greg Liras <gregliras@gmail.com>
#_._._._._._._._._._._._._._._._._._._._._.*/
from ctypes import *
from threading import Thread
from sys import argv

import os
path = os.path.dirname(os.path.realpath(__file__))
lib = CDLL("{0}/curse.so".format(path))


def curse(cmd,curse,target):
    return lib.curse(cmd,curse,target)

class thTassos(Thread):
    def __init__(self,cmd,curse,target):
        Thread.__init__(self)
        self.cmd = cmd
        self.curse = curse
        self.target = target

    def run(self):
        print curse(self.cmd, self.curse, self.target )

def main():
    if len(argv) != 5:
        print "Usage,{0} cmd, curse, target, threads".format(argv[0])
        exit(1)

    args = map(int,argv[1:])
    threads = []
    for i in range(args[3]):
        threads.append(thTassos(args[0], args[1], args[2]))
    map( lambda x : x.start(),threads )
    map( lambda x : x.join(),threads )

if __name__=="__main__":
    main()

