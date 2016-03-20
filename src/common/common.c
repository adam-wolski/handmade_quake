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
