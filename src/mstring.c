#include "mstring.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

void _mstr_free(MString str) {
        free(str->data);
        free(str);
}

/** Creates MString from given C style string 'cstr' **/
MString mstr_from_cstr(const char* cstr) {
        if (cstr == NULL) return NULL; 
        size_t cstrlen = strlen(cstr);
        MString str = calloc(1, sizeof(struct mstring));
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

void mstr_destroy(MString str) {
        _mstr_free(str);
}

unsigned char* mstr_to_chars(MString str) {
        return str->data;
}


/** Create MString from formated string **/
MString mstr_from_format(const char* fmt, ...)
{
        if (fmt == NULL) return NULL;

        /* Create small buffer and try calling vsnprintf which output will tell us the size 
         * needed for our output string */
        char* tmpstr = calloc(2, sizeof(char));
        if (!tmpstr) return NULL;
        va_list arglist;
        va_start(arglist, fmt); 
        int32_t r = vsnprintf(tmpstr, 2, fmt, arglist);
        va_end(arglist);
        if (r == -1) return NULL;
        free(tmpstr);

        /* vsnprintf gave us in return amount of space that was needed to fit whole string.
         * (excluding null character) */
        r += 1; /* Add that null character */
        char* str = calloc(r, sizeof(char));
        if (!str) return NULL;
        va_start(arglist, fmt); 
        r = vsnprintf(str, r, fmt, arglist);
        va_end(arglist);
        if (r == -1) return NULL;

        MString mstr =  mstr_from_cstr(str); 
        free(str);
        return mstr;
}

/**
 * Standard C style compare function.
 * Returns:
 *  0 if string are the same,
 * -1 if str1 is smaller
 *  1 if str1 is larger.
 **/
int32_t mstr_cmp(MString str1, MString str2) {
        if (str1 == NULL 
         || str2 == NULL 
         || str1->data == NULL 
         || str2->data == NULL) {
                /* Error */
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

/** Shorter compare function which just checks if two string are indentical **/
bool mstr_compare(MString str1, MString str2) {
        return mstr_cmp(str1, str2) == 0 ? true : false;
}
