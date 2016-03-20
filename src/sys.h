#pragma once
#include <stdio.h>
#include "quakedef.h"


f64 sys_get_time();

QResult sys_capture_events();


/**---------------------------------------------------------------------------------------
        File Handling */

typedef size_t FileHandleID;

QResult sys_file_open_read(MString path, FileHandleID* id, size_t* size);
QResult sys_file_open_write(MString path, FileHandleID* id);
QResult sys_file_close(FileHandleID id);
QResult sys_file_seek(FileHandleID id, size_t pos);
QResult sys_file_read(FileHandleID id, void* dest, size_t count);
QResult sys_file_write(FileHandleID id, void* data, size_t count);
