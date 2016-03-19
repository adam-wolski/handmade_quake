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


/**
 * Takes an explicit (not game tree related) path to a pak file.
 * 
 * Loads the header and directory, adding the files at the beginning
 * of the list so they override previous pack files.
**/
Pack* pack_load(MString path)
{
        PackFile* pack_files = NULL;
        Pack* pack = NULL;
        FileHandleID pack_handle; 
        size_t pack_size;

        check(sys_file_open_read(path, &pack_handle, &pack_size) == SYS_OK,
              "Failed to open pack file");

        PackHeaderDisk pack_header;
        check(sys_file_read(pack_handle, &pack_header, sizeof(PackHeaderDisk)) == SYS_OK, 
              "Failed to read a header from disk.");

        check(pack_header.magic[0] == 'P' &&
              pack_header.magic[1] == 'A' &&
              pack_header.magic[2] == 'C' &&
              pack_header.magic[3] == 'K',
              "Wrong File Header.");

        i32 pack_num_files = pack_header.dir_len / sizeof(PackFileDisk);

        pack_files = calloc(pack_num_files, sizeof(PackFile));

        check(sys_file_seek(pack_handle, pack_header.dir_offset) == SYS_OK,
              "Failed to seek to the directory offset.");

        PackFileDisk disk_files[PACK_MAX_FILES];
        check(sys_file_read(pack_handle, &disk_files, pack_header.dir_len) == SYS_OK,
              "Failed to read files from pack file.");

        for (int i = 0; i < pack_num_files; ++i) {
                memcpy(pack_files[i].filename, disk_files[i].filename, PACK_DISK_FILENAME_LEN); 
                pack_files->file_len = disk_files->file_len;
                pack_files->file_pos = disk_files->file_pos;
        }

        pack = calloc(1, sizeof(Pack));
        memcpy(pack->packname, path->data, PACK_NAME_LEN);
        pack->packname[PACK_NAME_LEN - 1] = '\0';

        pack->file_id = pack_handle;
        pack->num_files = pack_num_files;
        pack->pack_files = pack_files;

        return pack;        
error:
        if (pack_files) free(pack_files);
        if (pack) free(pack);
        return NULL;
}
