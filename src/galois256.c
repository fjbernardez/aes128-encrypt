#include "headers.h"

uint8_t gadd(uint8_t a, uint8_t b) {
	return a ^ b;
}

uint8_t gmul(uint8_t a, uint8_t b) {
	uint8_t p = 0;
	while (a && b) {
            if (b & 1) 
                p ^= a;

            if (a & 0x80)
                a = (a << 1) ^ 0x11b;
            else
                a <<= 1;
            b >>= 1; 
	}
	return p;
} 