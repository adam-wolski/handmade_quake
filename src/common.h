#pragma once
#include "quakedef.h"


/* Arguments management */
#define MAX_NUM_ARGVS 50
extern MString* com_argv;
extern size_t  com_argc;

QResult com_arg_init(const u32 argc, char** argv);
void com_arg_clear();
bool com_arg_check(const MString parm);


/* File management */
u8* com_file_find(MString file_name, i32* file_len);
QResult com_file_init();
void com_file_clear();


/* Other */
i32 com_atoi(const MString str);
