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
u8* com_file_find(MString file_name, size_t* file_size);
QResult com_file_init();
void com_file_clear();


/* Other */
i32 com_atoi(const MString str);
u32 com_3x8_to_32(u8* bytes);
u32 com_4x8_to_32(u8* bytes);
u32 com_4x8_to_32_inv(u8* bytes);
