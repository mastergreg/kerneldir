	{ 3,	TD,	sys_read,		"read"		},  /* 0 */
	{ 3,	TD,	sys_write,		"write"		},  /* 1 */
	{ 3,	TD|TF,	sys_open,		"open"		},  /* 2 */
	{ 1,	TD,	sys_close,		"close"		},  /* 3 */
	{ 2,	TF,	sys_stat,		"stat"		},  /* 4 */
	{ 2,	TD,	sys_fstat,		"fstat"		},  /* 5 */
	{ 2,	TF,	sys_lstat,		"lstat"		},  /* 6 */
	{ 3,	TD,	sys_poll,		"poll"		},  /* 7 */
	{ 3,	TD,	sys_lseek,		"lseek"		},  /* 8 */
	{ 6,	TD,	sys_mmap,		"mmap"		},  /* 9 */
	{ 3,	0,	sys_mprotect,		"mprotect"	},  /* 10 */
	{ 2,	0,	sys_munmap,		"munmap"	},  /* 11 */
	{ 1,	0,	sys_brk,		"brk"		},  /* 12 */
	{ },							    /* 13 */
	{ 4,	TS,	sys_rt_sigprocmask,	"rt_sigprocmask"},  /* 14 */
	{ },							    /* 15 */
	{ },							    /* 16 */
	{ 5,	TD,	sys_pread,		"pread"		},  /* 17 */
	{ 5,	TD,	sys_pwrite,		"pwrite"	},  /* 18 */
	{ },							    /* 19 */
	{ },							    /* 20 */
	{ 2,	TF,	sys_access,		"access"	},  /* 21 */
	{ 1,	TD,	sys_pipe,		"pipe"		},  /* 22 */
	{ 5,	TD,	sys_select,		"select"	},  /* 23 */
	{ 0,	0,	sys_sched_yield,	"sched_yield"	},  /* 24 */
	{ 5,	0,	sys_mremap,		"mremap"	},  /* 25 */
	{ 3,	0,	sys_msync,		"msync"		},  /* 26 */
	{ 3,	0,	sys_mincore,		"mincore"	},  /* 27 */
	{ 3,	0,	sys_madvise,		"madvise"	},  /* 28 */
	{ 4,	TI,	sys_shmget,		"shmget"	},  /* 29 */
	{ 4,	TI,	sys_shmat,		"shmat"		},  /* 30 */
	{ 4,	TI,	sys_shmctl,		"shmctl"	},  /* 31 */
	{ 1,	TD,	sys_dup,		"dup"		},  /* 32 */
	{ 2,	TD,	sys_dup2,		"dup2"		},  /* 33 */
	{ 0,	TS,	sys_pause,		"pause"		},  /* 34 */
	{ 2,	0,	sys_nanosleep,		"nanosleep"	},  /* 35 */
	{ 2,	0,	sys_getitimer,		"getitimer"	},  /* 36 */
	{ 1,	0,	sys_alarm,		"alarm"		},  /* 37 */
	{ 3,	0,	sys_setitimer,		"setitimer"	},  /* 38 */
	{ 0,	0,	sys_getpid,		"getpid"	},  /* 39 */
	{ 4,	TD|TN,	sys_sendfile,		"sendfile"	},  /* 40 */
	{ 3,	TN,	sys_socket,		"socket"	},  /* 41 */
	{ 3,	TN,	sys_connect,		"connect"	},  /* 42 */
	{ 3,	TN,	sys_accept,		"accept"	},  /* 43 */
	{ 6,	TN,	sys_sendto,		"sendto"	},  /* 44 */
	{ },							    /* 45 */
	{ },							    /* 46 */
	{ },							    /* 47 */
	{ 2,	TN,	sys_shutdown,		"shutdown"	},  /* 48 */
	{ 3,	TN,	sys_bind,		"bind"		},  /* 49 */
	{ 2,	TN,	sys_listen,		"listen"	},  /* 50 */
	{ 3,	TN,	sys_getsockname,	"getsockname"	},  /* 51 */
	{ 3,	TN,	sys_getpeername,	"getpeername"	},  /* 52 */
	{ 4,	TN,	sys_socketpair,		"socketpair"	},  /* 53 */
	{ 5,	TN,	sys_setsockopt,		"setsockopt"	},  /* 54 */
	{ 5,	TN,	sys_getsockopt,		"getsockopt"	},  /* 55 */
	{ 5,	TP,	sys_clone,		"clone"		},  /* 56 */
	{ 0,	TP,	sys_fork,		"fork"		},  /* 57 */
	{ 0,	TP,	sys_vfork,		"vfork"		},  /* 58 */
	{ },							    /* 47 */
	{ 1,	TP,	sys_exit,		"_exit"		},  /* 60 */
	{ 4,	TP,	sys_wait4,		"wait4"		},  /* 61 */
	{ 2,	TS,	sys_kill,		"kill"		},  /* 62 */
	{ 1,	0,	sys_uname,		"uname"		},  /* 63 */
	{ 4,	TI,	sys_semget,		"semget"	},  /* 64 */
	{ 4,	TI,	sys_semop,		"semop"		},  /* 65 */
	{ 4,	TI,	sys_semctl,		"semctl"	},  /* 66 */
	{ 4,	TI,	sys_shmdt,		"shmdt"		},  /* 67 */
	{ 4,	TI,	sys_msgget,		"msgget"	},  /* 68 */
	{ 4,	TI,	sys_msgsnd,		"msgsnd"	},  /* 69 */
	{ 5,	TI,	sys_msgrcv,		"msgrcv"	},  /* 70 */
	{ 3,	TI,	sys_msgctl,		"msgctl"	},  /* 71 */
	{ 3,	TD,	sys_fcntl,		"fcntl"		},  /* 72 */
	{ 2,	TD,	sys_flock,		"flock"		},  /* 73 */
	{ 1,	TD,	sys_fsync,		"fsync"		},  /* 74 */
	{ 1,	TD,	sys_fdatasync,		"fdatasync"	},  /* 75 */
	{ 2,	TF,	sys_truncate,		"truncate"	},  /* 76 */
	{ 2,	TD,	sys_ftruncate,		"ftruncate"	},  /* 77 */
	{ },							    /* 78 */
	{ 2,	TF,	sys_getcwd,		"getcwd"	},  /* 79 */
	{ 1,	TF,	sys_chdir,		"chdir"		},  /* 80 */
	{ 1,	TD,	sys_fchdir,		"fchdir"	},  /* 81 */
	{ 2,	TF,	sys_rename,		"rename"	},  /* 82 */
	{ 2,	TF,	sys_mkdir,		"mkdir"		},  /* 83 */
	{ 1,	TF,	sys_rmdir,		"rmdir"		},  /* 84 */
	{ 2,	TD|TF,	sys_creat,		"creat"		},  /* 85 */
	{ 2,	TF,	sys_link,		"link"		},  /* 86 */
	{ 1,	TF,	sys_unlink,		"unlink"	},  /* 87 */
	{ 2,	TF,	sys_symlink,		"symlink"	},  /* 88 */
	{ 3,	TF,	sys_readlink,		"readlink"	},  /* 89 */
	{ 2,	TF,	sys_chmod,		"chmod"		},  /* 90 */
	{ 2,	TD,	sys_fchmod,		"fchmod"	},  /* 91 */
	{ 3,	TF,	sys_chown,		"chown"		},  /* 92 */
	{ 3,	TD,	sys_fchown,		"fchown"	},  /* 93 */
	{ 3,	TF,	sys_chown,		"lchown"	},  /* 94 */
	{ 1,	0,	sys_umask,		"umask"		},  /* 95 */
	{ 2,	0,	sys_gettimeofday,	"gettimeofday"	},  /* 96 */
	{ 2,	0,	sys_getrlimit,		"getrlimit"	},  /* 97 */
	{ 2,	0,	sys_getrusage,		"getrusage"	},  /* 98 */
	{ 1,	0,	sys_sysinfo,		"sysinfo"	},  /* 99 */
	{ 1,	0,	sys_times,		"times"		},  /* 100 */
	{ },							    /* 101 */
	{ 0,	NF,	sys_getuid,		"getuid"	},  /* 102 */
	{ 3,	0,	sys_syslog,		"syslog"	},  /* 103 */
	{ 0,	NF,	sys_getgid,		"getgid"	},  /* 104 */
	{ 1,	0,	sys_setuid,		"setuid"	},  /* 105 */
	{ 1,	0,	sys_setgid,		"setgid"	},  /* 106 */
	{ 0,	NF,	sys_geteuid,		"geteuid"	},  /* 107 */
	{ 0,	NF,	sys_getegid,		"getegid"	},  /* 108 */
	{ 2,	0,	sys_setpgid,		"setpgid"	},  /* 109 */
	{ 0,	0,	sys_getppid,		"getppid"	},  /* 110 */
	{ 0,	0,	sys_getpgrp,		"getpgrp"	},  /* 111 */
	{ 0,	0,	sys_setsid,		"setsid"	},  /* 112 */
	{ 2,	0,	sys_setreuid,		"setreuid"	},  /* 113 */
	{ 2,	0,	sys_setregid,		"setregid"	},  /* 114 */
	{ 2,	0,	sys_getgroups,		"getgroups"	},  /* 115 */
	{ 2,	0,	sys_setgroups,		"setgroups"	},  /* 116 */
	{ 3,	0,	sys_setresuid,		"setresuid"	},  /* 117 */
	{ 3,	0,	sys_getresuid,		"getresuid"	},  /* 118 */
	{ 3,	0,	sys_setresgid,		"setresgid"	},  /* 119 */
	{ 3,	0,	sys_getresgid,		"getresgid"	},  /* 120 */
	{ 1,	0,	sys_getpgid,		"getpgid"	},  /* 121 */
	{ 1,	NF,	sys_setfsuid,		"setfsuid"	},  /* 122 */
	{ 1,	NF,	sys_setfsgid,		"setfsgid"	},  /* 123 */
	{ 1,	0,	sys_getsid,		"getsid"	},  /* 124 */
	{ 2,	0,	sys_capget,		"capget"	},  /* 125 */
	{ 2,	0,	sys_capset,		"capset"	},  /* 126 */
	{ },							    /* 127 */
	{ },							    /* 128 */
	{ },							    /* 129 */
	{ 2,	TS,	sys_rt_sigsuspend,	"rt_sigsuspend"	},  /* 130 */
	{ },							    /* 131 */
	{ 2,	TF,	sys_utime,		"utime"		},  /* 132 */
	{ 3,	TF,	sys_mknod,		"mknod"		},  /* 133 */
	{ },							    /* 134 */
	{ 1,	0,	sys_personality,	"personality"	},  /* 135 */
	{ 2,	0,	sys_ustat,		"ustat"		},  /* 136 */
	{ 2,	TF,	sys_statfs,		"statfs"	},  /* 137 */
	{ 2,	TD,	sys_fstatfs,		"fstatfs"	},  /* 138 */
	{ 3,	0,	sys_sysfs,		"sysfs"		},  /* 139 */
	{ 2,	0,	sys_getpriority,	"getpriority"	},  /* 140 */
	{ 3,	0,	sys_setpriority,	"setpriority"	},  /* 141 */
	{ 0,	0,	sys_sched_setparam,	"sched_setparam"	},  /* 142 */
	{ 2,	0,	sys_sched_getparam,	"sched_getparam"	},  /* 143 */
	{ 3,	0,	sys_sched_setscheduler,	"sched_setscheduler"	},  /* 144 */
	{ 1,	0,	sys_sched_getscheduler,	"sched_getscheduler"	},  /* 145 */
	{ 1,	0,	sys_sched_get_priority_max,	"sched_get_priority_max"	},  /* 146 */
	{ 1,	0,	sys_sched_get_priority_min,	"sched_get_priority_min"	},  /* 147 */
	{ 2,	0,	sys_sched_rr_get_interval,	"sched_rr_get_interval"	},  /* 148 */
	{ 2,	0,	sys_mlock,		"mlock"		},  /* 149 */
	{ 2,	0,	sys_munlock,		"munlock"	},  /* 150 */
	{ 1,	0,	sys_mlockall,		"mlockall"	},  /* 151 */
	{ 0,	0,	sys_munlockall,		"munlockall"	},  /* 152 */
	{ 0,	0,	sys_vhangup,		"vhangup"	},  /* 153 */
	{ 3,	0,	sys_modify_ldt,		"modify_ldt"	},  /* 154 */
	{ 2,	TF,	sys_pivotroot,		"pivot_root"	},  /* 155 */
	{ },							    /* 156 */
	{ 5,	0,	sys_prctl,		"prctl"		},  /* 157 */
	{ 2,	TP,	sys_arch_prctl,		"arch_prctl"	},  /* 158 */
	{ 1,	0,	sys_adjtimex,		"adjtimex"	},  /* 159 */
	{ 2,	0,	sys_setrlimit,		"setrlimit"	},  /* 160 */
	{ 1,	TF,	sys_chroot,		"chroot"	},  /* 161 */
	{ 0,	0,	sys_sync,		"sync"		},  /* 162 */
	{ 1,	TF,	sys_acct,		"acct"		},  /* 163 */
	{ 2,	0,	sys_settimeofday,	"settimeofday"	},  /* 164 */
	{ 5,	TF,	sys_mount,		"mount"		},  /* 165 */
	{ 2,	TF,	sys_umount2,		"umount"	}, /* 166 */
	{ 2,	TF,	sys_swapon,		"swapon"	},  /* 167 */
	{ 1,	TF,	sys_swapoff,		"swapoff"	},  /* 168 */
	{ 4,	0,	sys_reboot,		"reboot"	},  /* 169 */
	{ 2,	0,	sys_sethostname,	"sethostname"	},  /* 170 */
	{ 2,	0,	sys_setdomainname,	"setdomainname"	},  /* 171 */
	{ 1,	0,	sys_iopl,		"iopl"		},  /* 172 */
	{ 3,	0,	sys_ioperm,		"ioperm"	},  /* 173 */
	{ 2,	0,	sys_create_module,	"create_module"	},  /* 174 */
	{ 3,	0,	sys_init_module,	"init_module"	},  /* 175 */
	{ 2,	0,	sys_delete_module,	"delete_module"	},  /* 176 */
	{ },							    /* 177 */
	{ },							    /* 178 */
	{ 4,	0,	sys_quotactl,		"quotactl"	},  /* 179 */
	{ },							    /* 180 */
	{ },							    /* 181 */
	{ },							    /* 182 */
	{ },							    /* 183 */
	{ },							    /* 184 */
	{ },							    /* 185 */
	{ 0,	0,	sys_gettid,		"gettid"	}, /* 186 */
	{ 4,	TD,	sys_readahead,		"readahead"	}, /* 187 */
	{ 5,	TF,	sys_setxattr,		"setxattr"	}, /* 188 */
	{ 5,	TF,	sys_setxattr,		"lsetxattr"	}, /* 189 */
	{ 5,	TD,	sys_fsetxattr,		"fsetxattr"	}, /* 190 */
	{ 4,	TF,	sys_getxattr,		"getxattr"	}, /* 191 */
	{ 4,	TF,	sys_getxattr,		"lgetxattr"	}, /* 192 */
	{ 4,	TD,	sys_fgetxattr,		"fgetxattr"	}, /* 193 */
	{ 3,	TF,	sys_listxattr,		"listxattr"	}, /* 194 */
	{ 3,	TF,	sys_listxattr,		"llistxattr"	}, /* 195 */
	{ 3,	TD,	sys_flistxattr,		"flistxattr"	}, /* 196 */
	{ 2,	TF,	sys_removexattr,	"removexattr"	}, /* 197 */
	{ 2,	TF,	sys_removexattr,	"lremovexattr"	}, /* 198 */
	{ 2,	TD,	sys_fremovexattr,	"fremovexattr"	}, /* 199 */
	{ 2,	TS,	sys_kill,		"tkill"		}, /* 200 */
	{ 1,	0,	sys_time,		"time"		},  /* 201 */
	{ 6,	0,	sys_futex,		"futex"		}, /* 202 */
	{ 3,	0,	sys_sched_setaffinity,	"sched_setaffinity" },/* 203 */
	{ 3,	0,	sys_sched_getaffinity,	"sched_getaffinity" },/* 204 */
	{ },							   /* 205 */
	{ 2,	0,	sys_io_setup,		"io_setup"	}, /* 206 */
	{ 1,	0,	sys_io_destroy,		"io_destroy"	}, /* 207 */
	{ 5,	0,	sys_io_getevents,	"io_getevents"	}, /* 208 */
	{ 3,	0,	sys_io_submit,		"io_submit"	}, /* 209 */
	{ 3,	0,	sys_io_cancel,		"io_cancel"	}, /* 210 */
	{ },							   /* 211 */
	{ 4,	0,	sys_lookup_dcookie,	"lookup_dcookie"}, /* 212 */
	{ 1,	TD,	sys_epoll_create,	"epoll_create"	}, /* 213 */
	{ },							   /* 214 */
	{ },							   /* 215 */
	{ 5,	0,	sys_remap_file_pages,	"remap_file_pages"}, /* 216 */
	{ 3,	TD,	sys_getdents64,		"getdents64"	}, /* 217 */
	{ 1,	0,	sys_set_tid_address,	"set_tid_address"}, /* 218 */
	{ 0,	0,	sys_restart_syscall,	"restart_syscall"}, /* 219 */
	{ 5,	TI,	sys_semtimedop,		"semtimedop"	}, /* 220 */
	{ 4,	TD,	sys_fadvise64_64,	"fadvise64"	}, /* 221 */
	{ },							   /* 222 */
	{ 4,	0,	sys_timer_settime,	"timer_settime"	}, /* 223 */
	{ 2,	0,	sys_timer_gettime,	"timer_gettime"	}, /* 224 */
	{ 1,	0,	sys_timer_getoverrun,	"timer_getoverrun"}, /* 225 */
	{ 1,	0,	sys_timer_delete,	"timer_delete"	}, /* 226 */
	{ 2,	0,	sys_clock_settime,	"clock_settime"	}, /* 227 */
	{ 2,	0,	sys_clock_gettime,	"clock_gettime"	}, /* 228 */
	{ 2,	0,	sys_clock_getres,	"clock_getres"	}, /* 229 */
	{ 4,	0,	sys_clock_nanosleep,	"clock_nanosleep"}, /* 230 */
	{ 1,	TP,	sys_exit,		"exit_group"	}, /* 231 */
	{ 4,	TD,	sys_epoll_wait,		"epoll_wait"	}, /* 232 */
	{ 4,	TD,	sys_epoll_ctl,		"epoll_ctl"	}, /* 233 */
	{ 3,	TS,	sys_tgkill,		"tgkill"	}, /* 234 */
	{ 2,	TF,	sys_utimes,		"utimes"	}, /* 235 */
	{ },							   /* 236 */
	{ 6,	0,	sys_mbind,		"mbind"		}, /* 237 */
	{ 3,	0,	sys_set_mempolicy,	"set_mempolicy"	}, /* 238 */
	{ 5,	0,	sys_get_mempolicy,	"get_mempolicy"	}, /* 239 */
	{ 4,	0,	sys_mq_open,		"mq_open"	}, /* 240 */
	{ 1,	0,	sys_mq_unlink,		"mq_unlink"	}, /* 241 */
	{ 5,	0,	sys_mq_timedsend,	"mq_timedsend"	}, /* 242 */
	{ 5,	0,	sys_mq_timedreceive,	"mq_timedreceive" }, /* 243 */
	{ },							   /* 244 */
	{ 3,	0,	sys_mq_getsetattr,	"mq_getsetattr"	}, /* 245 */
	{ },							   /* 246 */
	{ },							   /* 247 */
	{ 5,	0,	sys_add_key,		"add_key"	}, /* 248 */
	{ 4,	0,	sys_request_key,	"request_key"	}, /* 249 */
	{ 5,	0,	sys_keyctl,		"keyctl"	}, /* 250 */
	{ 3,	0,	sys_ioprio_set,		"ioprio_set"	}, /* 251 */
	{ 2,	0,	sys_ioprio_get,		"ioprio_get"	}, /* 252 */
	{ 0,	TD,	sys_inotify_init,	"inotify_init"	}, /* 253 */
	{ 3,	TD,	sys_inotify_add_watch,	"inotify_add_watch" }, /* 254 */
	{ 2,	TD,	sys_inotify_rm_watch,	"inotify_rm_watch" }, /* 255 */
	{ 4,	0,	sys_migrate_pages,	"migrate_pages"	}, /* 256 */
	{ 4,	TD|TF,	sys_openat,		"openat"	}, /* 257 */
	{ 3,	TD|TF,	sys_mkdirat,		"mkdirat"	}, /* 258 */
	{ 4,	TD|TF,	sys_mknodat,		"mknodat"	}, /* 259 */
	{ 5,	TD|TF,	sys_fchownat,		"fchownat"	}, /* 260 */
	{ 3,	TD|TF,	sys_futimesat,		"futimesat"	}, /* 261 */
	{ 4,	TD|TF,	sys_newfstatat,		"newfstatat"	}, /* 262 */
	{ 3,	TD|TF,	sys_unlinkat,		"unlinkat"	}, /* 263 */
	{ 4,	TD|TF,	sys_renameat,		"renameat"	}, /* 264 */
	{ 5,	TD|TF,	sys_linkat,		"linkat"	}, /* 265 */
	{ 3,	TD|TF,	sys_symlinkat,		"symlinkat"	}, /* 266 */
	{ 4,	TD|TF,	sys_readlinkat,		"readlinkat"	}, /* 267 */
	{ 3,	TD|TF,	sys_fchmodat,		"fchmodat"	}, /* 268 */
	{ 3,	TD|TF,	sys_faccessat,		"faccessat"	}, /* 269 */
	{ 6,	TD,	sys_pselect6,		"pselect6"	}, /* 270 */
	{ 5,	TD,	sys_ppoll,		"ppoll"		}, /* 271 */
	{ 1,	TP,	sys_unshare,		"unshare"	}, /* 272 */
	{ },							   /* 273 */
	{ },							   /* 274 */
	{ 6,	TD,	sys_splice,		"splice"	}, /* 275 */
	{ 4,	TD,	sys_tee,		"tee"		}, /* 276 */
	{ 4,	TD,	sys_sync_file_range,	"sync_file_range" }, /* 277 */
	{ },							   /* 278 */
	{ },							   /* 279 */
	{ 4,	TD|TF,	sys_utimensat,		"utimensat"	}, /* 280 */
	{ 6,	TD,	sys_epoll_pwait,	"epoll_pwait"	}, /* 281 */
	{ 3,	TD|TS,	sys_signalfd,		"signalfd"	}, /* 282 */
	{ 2,	TD,	sys_timerfd_create,	"timerfd_create"}, /* 283 */
	{ 1,	TD,	sys_eventfd,		"eventfd"	}, /* 284 */
	{ 6,	TD,	sys_fallocate,		"fallocate"	}, /* 285 */
	{ 4,	TD,	sys_timerfd_settime,	"timerfd_settime"}, /* 286 */
	{ 2,	TD,	sys_timerfd_gettime,	"timerfd_gettime"}, /* 287 */
	{ 4,	TN,	sys_accept4,		"accept4"	}, /* 288 */
	{ 4,	TD|TS,	sys_signalfd4,		"signalfd4"	}, /* 289 */
	{ 2,	TD,	sys_eventfd2,		"eventfd2"	}, /* 290 */
	{ 1,	TD,	sys_epoll_create1,	"epoll_create1"	}, /* 291 */
	{ 3,	TD,	sys_dup3,		"dup3"		}, /* 292 */
	{ 2,	TD,	sys_pipe2,		"pipe2"		}, /* 293 */
	{ 1,	TD,	sys_inotify_init1,	"inotify_init1"	}, /* 294 */
	{ },							   /* 295 */
	{ },							   /* 296 */
	{ },							   /* 297 */
	{ 5,	TD,	sys_perf_event_open,	"perf_event_open"}, /* 298 */
	{ },							   /* 299 */
	{ 2,	TD,	sys_fanotify_init,	"fanotify_init"	}, /* 300 */
	{ 5,	TD|TF,	sys_fanotify_mark,	"fanotify_mark"	}, /* 301 */
	{ 4,	0,	sys_prlimit64,		"prlimit64"	}, /* 302 */
	{ 5,	TD|TF,	sys_name_to_handle_at,	"name_to_handle_at"}, /* 303 */
	{ 3,	TD,	sys_open_by_handle_at,	"open_by_handle_at"}, /* 304 */
	{ 2,	0,	sys_clock_adjtime,	"clock_adjtime"	}, /* 305 */
	{ 1,	TD,	sys_syncfs,		"syncfs"	}, /* 306 */
	{ },							   /* 307 */
	{ 2,	TD,	sys_setns,		"setns"		}, /* 308 */
	{ 3,	0,	sys_getcpu,		"getcpu"	}, /* 309 */
	{ },							   /* 310 */
	{ },							   /* 311 */

	[312 ... 340] = {},
	{ 5,	TP,	sys_curse,	"curse"	},	/* 341 */
	[342 ... 511] = {},

	{ 4,	TS,	sys_rt_sigaction,	"rt_sigaction"	},  /* 512 */
	{ 0,	TS,	sys_rt_sigreturn,	"rt_sigreturn"	},  /* 513 */
	{ 3,	TD,	sys_ioctl,		"ioctl"		},  /* 514 */
	{ 3,	TD,	sys_readv,		"readv"		},  /* 515 */
	{ 3,	TD,	sys_writev,		"writev"	},  /* 516 */
	{ 6,	TN,	sys_recvfrom,		"recvfrom"	},  /* 517 */
	{ 3,	TN,	sys_sendmsg,		"sendmsg"	},  /* 518 */
	{ 5,	TN,	sys_recvmsg,		"recvmsg"	},  /* 519 */
	{ 3,	TF|TP,	sys_execve,		"execve"	},  /* 520 */
	{ 4,	0,	sys_ptrace,		"ptrace"	},  /* 521 */
	{ 2,	TS,	sys_rt_sigpending,	"rt_sigpending"	},  /* 522 */
	{ 4,	TS,	sys_rt_sigtimedwait,	"rt_sigtimedwait" },  /* 523 */
	{ 3,	TS,	sys_rt_sigqueueinfo,    "rt_sigqueueinfo" },  /* 524 */
	{ 2,	TS,	sys_sigaltstack,	"sigaltstack"	},  /* 525 */
	{ 3,	0,	sys_timer_create,	"timer_create"	}, /* 526 */
	{ 2,	0,	sys_mq_notify,		"mq_notify"	}, /* 527 */
	{ 4,	0,	sys_kexec_load,		"kexec_load"	}, /* 528 */
	{ 5,	TP,	sys_waitid,		"waitid"	}, /* 529 */
	{ 2,	0,	sys_set_robust_list,	"set_robust_list" }, /* 530 */
	{ 3,	0,	sys_get_robust_list,	"get_robust_list" }, /* 531 */
	{ 4,	TD,	sys_vmsplice,		"vmsplice"	}, /* 532 */
	{ 6,	0,	sys_move_pages,		"move_pages"	}, /* 533 */
	{ 5,	TD,	sys_preadv,		"preadv"	}, /* 534 */
	{ 5,	TD,	sys_pwritev,		"pwritev"	}, /* 535 */
	{ 4,	TP|TS,	sys_rt_tgsigqueueinfo,	"rt_tgsigqueueinfo"}, /* 536 */
	{ 5,	TN,	sys_recvmmsg,		"recvmmsg"	}, /* 537 */
	{ 4,	TN,	sys_sendmmsg,		"sendmmsg"	}, /* 538 */
	{ 6,	0,	sys_process_vm_readv,	"process_vm_readv"}, /* 539 */
	{ 6,	0,	sys_process_vm_writev,	"process_vm_writev"}, /* 540 */
