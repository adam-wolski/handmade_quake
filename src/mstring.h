#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct mstring {
	size_t mlen; /* Memory size */
	size_t slen; /* String length (Only characters, without ending NULL) */
	unsigned char* data;
};
typedef struct mstring* MString;

typedef enum {
        MSTR_OK,
        MSTR_FAILED,
        MSTR_ERROR
}MSTR_RESULT;

MString mstr_from_cstr(const char* cstr);
unsigned char* mstr_to_chars(MString str);
MSTR_RESULT mstr_destroy(MString str);
int32_t mstr_cmp(MString str1, MString str2); /* Standard C style cmp */
bool mstr_compare(MString str1, MString str2); /* cmp with bool result. */
