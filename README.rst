============================
Linux Curses
============================
Linux Curses is a framework that enables kernel-mode operations, called curses, to be inflicted upon running processes. Each curse can be inheritable, has its own private data, its own cross-curse permission system and can inflict any kind of kernel-space action with the appropriate code injections.

Curses was developed for the linux 2.6.37.4 kernel and is available as a patch.
Along with it, comes a userspace library that provides access to the system call, and a python tool for easy usage.


==================
Available Actions
==================
The curse system call provides the following actions for any curse:

List all curses
Activate a curse globally
Deactivate it globally
Cast it on a process
Lift it from a process
Check if a process is cursed
Check if a curse is used on any process

==================
Implemented Curses
==================
Curses comes with a total of 6 already implemented curses:

no_exit
=======
When the inflicted process dies, it will remain a zombie until the curse is lifted or deactivated.

no_fs_cache
==========
Prevents the inflicted process from caching data using the sys_fadvise call.

poison
==========
The inflicted process dies after a predetermined ammount of schedules.

random_oops
==========
A kernel oops happens at a random, unless the curse is lifted in time.

no_curse
==========
Disables a process from cursing other processes
