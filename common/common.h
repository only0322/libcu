#ifndef _COMMON_H_
#define _COMMON_H_
#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<math.h>

#ifdef _WIN32

#else
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/timeb.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<unistd.h>
#endif
#include<time.h>

#include<ctype.h>

#include<dirent.h>
#include<signal.h>
#include<memory.h>
#include<stdarg.h>
#endif
