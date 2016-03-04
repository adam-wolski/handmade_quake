#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct mstring {
	size_t mlen; /* Memory size */
	size_t slen; /* String length (Only characters, without ending NULL) */
	unsigned char* data;
};
typedef struct mstring* Mstring;

typedef enum {
        MSTR_OK,
        MSTR_FAILED,
        MSTR_ERROR
}MSTR_RESULT;

Mstring mstr_from_cstr(const char* cstr);
unsigned char* mstr_to_chars(Mstring str);
MSTR_RESULT mstr_destroy(Mstring str);
int32_t mstr_cmp(Mstring str1, Mstring str2); /* Standard C style cmp */
bool mstr_compare(Mstring str1, Mstring str2); /* cmp with bool result. */
