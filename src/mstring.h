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

MString mstr_from_cstr(const char* cstr);
MString mstr_from_format(const char* fmt, ...);
unsigned char* mstr_to_chars(MString str);
void mstr_destroy(MString str);
int32_t mstr_cmp(MString str1, MString str2); /* Standard C style cmp */
bool mstr_compare(MString str1, MString str2); /* cmp with bool result. */
