#ifndef __UTILS__
#define __UTILS__

#include <stdint.h>

void show_matrix(char* label, uint8_t m_resultado[][4]);
void show_vector(char* label, uint8_t * v_resultado, uint8_t size);
void char_to_bin(uint8_t val);

#endif //  __UTILS__

