#include "sys.h"
#include "sdl.h"

/** Return elapsed time in seconds since program started **/
f64 sys_get_time()
{
        /* Sdl returns time in milliseconds */
        return (f64)sdl_get_ticks() / 1000.0;
}

QResult sys_capture_events()
{
        if (!sdl_capture_events()) {
                IS_RUNNING = false;
        }

        return Q_OK;
}


/**---------------------------------------------------------------------------------------
        File Handling */
/*
 * Maximum amount of file handles that can be created. Doesn't need to be big, there will be
 * propably just a few .pak files. Original Quake sets this one to 10.
 */
#define	MAX_HANDLES 10

/* File handles */
static FILE* SYS_HANDLES[MAX_HANDLES] = {0};


/** If possible assign an empty file handle to 'id'. **/
static QResult find_handle(FileHandleID* id)
{
        for (size_t i = 0; i < MAX_HANDLES; ++i) {
                if (!SYS_HANDLES[i]) {
                        *id = i;
                        log_info("Found empty handle: %ld.", i);
                        return Q_OK;
                }
        }

        /*
         * Original quake panics with Sys_Error() in here which closes whole game.
         * I'm not sure it's necessary.
         * I prefer to leave it to the user of find_handle to deal with handle not being available.
         */
        log_err("Couldn't find empty handle.");
        return Q_ERR;
}

/** Check if file handle id is correct **/
inline static bool check_handle_id(FileHandleID id)
{
        return id < MAX_HANDLES - 1;
}

/** Find end position of a file 'f'. **/
static size_t file_end(FILE* f)
{
        /* Hold start position so we can return back to it later */
        size_t pos = ftell(f);
        fseek(f, 0, SEEK_END);
        size_t end = ftell(f);
        fseek(f, pos, SEEK_SET);
        return end;
}

/** 
 * Open and setup the file from the path 'path' in the mode 'mode'.
 * Fills file handle 'id' if possible otherwise returns Q_ERR.
 * FilePos 'end' is filled with amount of bytes from beggining to end of the file.
 **/
static QResult file_open(MString path, const char* mode, FileHandleID* id, size_t* size)
{
        unsigned char* cpath = mstr_to_chars(path);

        /* Try to assign a handle id */
        check(find_handle(id), "Couldn't get file handle.");

        FILE* f = fopen((const char*)cpath, mode);
        check(f, "Couldn't open the file: %s", cpath);

        SYS_HANDLES[*id] = f;

        *size = file_end(f); 

        log_info("Opened file %s with length of %ld bytes and assigned it ID %ld",
                 cpath, *size, *id);

        return Q_OK;
error:
        *id = -1;
        *size = -1;
        return Q_ERR;
}

/** Open file for reading. **/
QResult sys_file_open_read(MString path, FileHandleID* id, size_t* size) 
{
        return file_open(path, "rb", id, size);
}

/** Open file for writing **/
QResult sys_file_open_write(MString path, FileHandleID* id)
{
        /* Length of the file doesn't matter when we're writing */
        size_t tmp;
        return file_open(path, "wb", id, &tmp);
}

/** Close the file **/
QResult sys_file_close(FileHandleID id)
{
        check(check_handle_id(id), "Wrong handle id: %ld", id);
        check(fclose(SYS_HANDLES[id]) == 0, "Failed to close the file.");
        SYS_HANDLES[id] = NULL;
        log_info("Closed file with id: %ld", id);
        return Q_OK;
error:
        return Q_ERR;
}

/** Change position indenticator for file to position 'pos'. **/
QResult sys_file_seek(FileHandleID id, size_t pos)
{        
        check(check_handle_id(id), "Wrong handle id: %ld", id);
        check(fseek(SYS_HANDLES[id], pos, SEEK_SET) == 0, "Failed to seek in file.");
        return Q_OK;
error:
        return Q_ERR;
}

/** Read 'count' amount of data in bytes from file to destination 'dest' **/
QResult sys_file_read(FileHandleID id, void* dest, size_t count)
{
        check(check_handle_id(id), "Wrong handle id: %ld", id);
        size_t bytes_read = fread(dest, 1, count, SYS_HANDLES[id]);
        if (bytes_read != count) {
                log_warn("Read different amount of data then specified.");
                return Q_WARN;
        }
        return Q_OK;
error:
        return Q_ERR;
}

/** Write 'count' amount of data in bytes from 'data' to file **/
QResult sys_file_write(FileHandleID id, void* data, size_t count)
{
        check(check_handle_id(id), "Wrong handle id: %ld", id);
        size_t bytes_written = fwrite(data, 1, count, SYS_HANDLES[id]);
        if (bytes_written != count) {
                log_warn("Written different amount of data then specified.");
                return Q_WARN;
        }
        return Q_OK;
error:
        return Q_ERR;
}
