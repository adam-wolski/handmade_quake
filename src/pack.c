#include "pack.h"

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
