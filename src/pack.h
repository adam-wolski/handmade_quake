#pragma once
#include "quakedef.h"

/* Maximum amount of files in PACK file. Original Quake: 2048 */
#define PACK_MAX_FILES 2048
/* Maximum amount of characters in filename of the file stored on disk. Original Quake: 56 */
#define PACK_DISK_FILENAME_LEN 56
/* 
 * Maximum amount of characters in filename of the file stored in memory. For some reason in quake
 * this one is different then one stored on disk. Original Quake: 64; defined as MAX_QPATH.
 */
#define PACK_MEM_FILENAME_LEN PACK_DISK_FILENAME_LEN
/* Maximum amount of characters in PACK file name. Original Quake: 128; defines as MAX_OSPATH */
#define PACK_NAME_LEN 128


/* Header of the pack file stored on disk */
typedef struct {
        /* Magic bytes of the quake pack file, should be 'PACK' for valid signature. */
        char magic[4];
        /* Amount of bytes from beginning of the file to start of directories. */
        i32 dir_offset;
        /* Amount of bytes that those directories specifications take. */
        i32 dir_len;
}PackHeaderDisk;

/* File data on disk */
typedef struct {
        char filename[PACK_DISK_FILENAME_LEN];
        i32  file_pos;
        i32  file_len;
}PackFileDisk;

/* File data in memory */
typedef struct {
        char filename[PACK_MEM_FILENAME_LEN];
        i32  file_pos;
        i32  file_len;
}PackFile;

/* Pack file we end up with storing all the previous data */
typedef struct {
        char packname[PACK_NAME_LEN];       
        FileHandleID file_id;
        size_t num_files;
        PackFile* pack_files;
}Pack;


Pack* pack_load(MString path);
