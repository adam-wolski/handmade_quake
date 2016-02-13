#include "mstring.h"
#include <string.h>
#include <stdlib.h>

void _mstr_free(Mstring str) {
        free(str->data);
        free(str);
}

/*
 * Creates Mstring from given C style string 'cstr'
 */
Mstring mstr_from_cstr(const char* cstr) {
        if (cstr == NULL) return NULL; 
        size_t cstrlen = strlen(cstr);
        Mstring str = calloc(1, sizeof(struct mstring));
        if (str == NULL) return NULL;
        str->slen = cstrlen;
        str->mlen = cstrlen + 1;
        str->data = calloc(str->mlen, sizeof(unsigned char));
        if (str->data == NULL) {
                free(str);
                return NULL;
        }
        memcpy(str->data, cstr, cstrlen + 1);
        return str;
}

MSTR_RESULT mstr_destroy(Mstring str) {
        _mstr_free(str);
        return MSTR_OK;
}

unsigned char* mstr_to_chars(Mstring str) {
        return str->data;
}

/*
 * Standard C style compare function.
 * Returns:
 *  0 if string are the same,
 * -1 if str1 is smaller
 *  1 if str1 is larger.
 */
int32_t mstr_cmp(Mstring str1, Mstring str2) {
        if (str1 == NULL 
         || str2 == NULL 
         || str1->data == NULL 
         || str2->data == NULL) {
                // Error
                return -1;
        }
        if (str1->slen == 0 && str2->slen == 0) {
                return 0;
        }
        size_t n = str1->slen > str2->slen ? str1->slen : str2->slen;
        for (size_t i = 0; i < n; ++i) {
                if (str1->data[i] != str2->data[i]) {
                       return str1->slen > str2->slen ? 1 : -1;
                }
        }
        return 0;
}

bool mstr_compare(Mstring str1, Mstring str2) {
        return mstr_cmp(str1, str2) == 0 ? true : false;
}
