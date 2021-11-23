#ifndef __AES__
#define __AES__

#include <stdint.h>
#include <stdlib.h>

void add_round_key(uint8_t m_clave[][4], uint8_t m_estado[][4]);
void sub_bytes(uint8_t m_estado[][4]);
void shift_rows(uint8_t m_estado[][4]);
void mix_columns(uint8_t m_estado[][4]);
void key_expansion(uint8_t m_clave[][4], uint8_t round);

uint8_t* get_colum(uint8_t m_clave[][4], uint8_t colum);
void insert_column(uint8_t m_clave[][4], uint8_t* colum_buffer, uint8_t colum);
void sub_bytes_vector(uint8_t* colum);
void xor_vector(uint8_t* vector_a, const uint8_t* vector_b, uint8_t size);
void shift_row(uint8_t* row, uint8_t n);

void encrypt_matrix(uint8_t m_estado[][4], uint8_t m_clave[][4]);

#endif //  __AES__




