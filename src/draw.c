#include "draw.h"


void draw_lump(i32 x, i32 y, u8* lump_data)
{
        u8* lmp = lump_data;

        u32 width = com_4x8_to_32_inv(lmp);
        lmp += 4;
        u32 height = com_4x8_to_32_inv(lmp);
        lmp += 4;

        u32* dest = VID.backbuffer;

        dest += (VID.buf_width * y) + x;
        
        u32* walker = dest;

        for (u32 h = 0; h < height; h++) {
                for (u32 w = 0; w < width; w++) {
                        u32 clr = VID.palette[*lmp];
                        if (*lmp != 0xff)
                                *walker = clr;
                        walker++;
                        lmp++;
                }
                dest += VID.buf_width;
                walker = dest;
        }

}
