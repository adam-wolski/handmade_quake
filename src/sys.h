#pragma once
#include <stdio.h>
#include "quakedef.h"


/*
 * Maximum amount of file handles that can be created. Doesn't need to be big, there will be
 * propably just a few .pak files. Original Quake sets this one to 10.
 */
#define	MAX_HANDLES 10


typedef enum {
        SYS_OK,
        SYS_WARN,
        SYS_ERR,
}SYS_RESULT;


f64 sys_get_time();

SYS_RESULT sys_capture_events();


/**---------------------------------------------------------------------------------------
        File Handling */

typedef size_t FileHandleID;

SYS_RESULT sys_file_open_read(MString path, FileHandleID* id, size_t* size);
SYS_RESULT sys_file_open_write(MString path, FileHandleID* id);
SYS_RESULT sys_file_close(FileHandleID id);
SYS_RESULT sys_file_seek(FileHandleID id, size_t pos);
SYS_RESULT sys_file_read(FileHandleID id, void* dest, size_t count);
SYS_RESULT sys_file_write(FileHandleID id, void* data, size_t count);
