#include "../common.h"

/** Convert string to integer value. **/
i32 com_atoi(const MString str) 
{
        unsigned char* data = mstr_to_chars(str);
        size_t len = str->slen;
        size_t i = 0;
        i32 result = 0;
        i32 mul = 1;
        if (data[i] == '-') {
                mul = -1;
                ++i;
        }
        // Hex
        if (data[i] == '0' && (data[i+1] == 'x' || data[i+1] == 'X')) {
                i += 2;
                while (i < len) {
                        if (data[i] >= '0' && data[i] <= '9') {
                                result = result * 16 + data[i++] - '0'; 
                        } else if (data[i] >= 'a' && data[i] <= 'f') {
                                result = result * 16 + data[i++] - 'a' + 10;
                        } else if (data[i] >= 'A' && data[i] <= 'F') {
                                result = result * 16 + data[i++] - 'A' + 10;
                        } else {
                                break;
                        }
                }
                return result * mul;
        }

        // Decimal
        while (i < len) {
                if (data[i] < '0' || data[i] > '9') {
                        break;
                }
                result = result * 10 + data[i++] - '0'; 
        }

        return result * mul;
}

/** Convert 3 8bit values to one 32bit value **/
u32 com_3x8_to_32(u8* bytes)
{
        return ((bytes[0] << 16) | (bytes[1] << 8) | bytes[2]);
}

/** Convert 4 8bit values to one 32bit value **/
u32 com_4x8_to_32(u8* bytes)
{
        return ((bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3]);
}

/** Convert 4 8bit values to one 32bit value **/
u32 com_4x8_to_32_inv(u8* bytes)
{
        return ((bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | bytes[0]);
}
