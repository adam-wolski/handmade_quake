/*
 * Like in original Quake this one header is included everywhere so don't define anything in here,
 * unless you want redefinition errors.
 */

/* System headers */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h> /* For false and true boolean */
#include <stdlib.h>
#include <stdio.h>

/* Local headers */
#include "debug.h"
#include "mstring.h"
#include "common.h"
#include "sys.h"
#include "host.h"
#include "vid.h"

/**---------------------------------------------------------------------------------------
        Basic type typedef */

typedef uint8_t u8;
typedef uint32_t u32;
typedef int32_t i32;
/* TODO Make stdfloat version of stdint with checks for availible precision on system */
typedef float f32;
typedef double f64;


/**---------------------------------------------------------------------------------------
        Global game variables */

/* Those sit in host.c */
extern bool IS_RUNNING;
extern f64 TARGET_FPS;
