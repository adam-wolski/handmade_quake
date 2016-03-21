#include "../common.h"
#include "../pack.h"


/* Simple linked list that Quake uses for storing loaded .pak files */
typedef struct SearchPathStruct {
        Pack* pack;
        struct SearchPathStruct* next;
}SearchPath;

SearchPath* SEARCH_PATH = NULL;

/** 
 * Search for .pak files in directory 'dir' and add them to SEARCH_PATH. 
 * 'dir' has to be path written in unix style with '/' as separators and end with directory name
 * without '/' after it.
 * Pack files have to be named in order pak0.pak, pak1.pak and so on.
 **/
static QResult add_game_dir(MString dir)
{
        Pack* pack;
        int i = -1;
        while (true) {
                /* TODO Look into maybe changing input for pack_load to const char so we don't have
                 * to allocate memory on the heap everytime. */
                MString path = mstr_from_format("%s/pak%d.pak", mstr_to_chars(dir), ++i);
                pack = pack_load(path);
                mstr_destroy(path);
                if (!pack) {
                        break;
                }
                SearchPath* new_path = calloc(1, sizeof(SearchPath));
                check_mem(new_path);
                new_path->pack = pack;
                new_path->next = SEARCH_PATH;
                SEARCH_PATH = new_path;
        }
        return Q_OK; 
error:
        return Q_ERR;
}

static void clear_searchpath()
{
        while(SEARCH_PATH)
        {
                SearchPath* delete = SEARCH_PATH;
                SEARCH_PATH = SEARCH_PATH->next;
                pack_destroy(delete->pack);
                free(delete);
        }
}

/** 
 * Search for file with name 'file_name' in loaded .pak files.
 * If found pointer to file data will be returned  and 'file_size' will hold amount of bytes that
 * this file has.
 * Otherwise NULL is returned and file_size is made 0.
 **/
u8* com_file_find(MString file_name, size_t* file_size)
{
        u8* file = NULL;
        check_mem(file_size);
        SearchPath* walker;
        for (walker = SEARCH_PATH; walker != NULL; walker = walker->next)
        {
                Pack* pack = walker->pack;
                for (size_t i = 0; i < pack->num_files; ++i) {
                        if (strcmp((const char*)mstr_to_chars(file_name),
                                   pack->pack_files[i].filename)) 
                        {
                                FileHandleID fid = pack->file_id;
                                i32 fpos = pack->pack_files[i].file_pos;
                                i32 flen = pack->pack_files[i].file_len;
                                sys_file_seek(fid, fpos);

                                file = calloc(flen, sizeof(u8));
                                check_mem(file);
                                check(sys_file_read(fid, file, flen),
                                      "Failed to read data from file.");
                                *file_size = flen;
                                return file;
                        }
                }
        }
error:
        if (file) free(file);
        if (file_size) *file_size = 0;
        return NULL;
}

/** Add known folders to game and search for .pak files in them **/
QResult com_file_init()
{
        MString gamedir = mstr_from_cstr("content/id1");
        check(add_game_dir(gamedir), "Failed to add game directory");
        mstr_destroy(gamedir);
        return Q_OK;
error:
        mstr_destroy(gamedir);
        return Q_ERR;
}

/** Clear all the loaded files **/
void com_file_clear()
{
        clear_searchpath();        
}
