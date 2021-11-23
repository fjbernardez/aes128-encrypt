#include "headers.h"

#define NUMBER_OF_ROUNDS 10 

const uint8_t m_constante[4][4] = {
	{0x02, 0x03, 0x01, 0x01},
	{0x01, 0x02, 0x03, 0x01},
	{0x01, 0x01, 0x02, 0x03},
	{0x03, 0x01, 0x01, 0x02},
};

const uint8_t m_rcon[11][4] = {
	{0x00, 0x00, 0x00, 0x00}, // not used
	{0x01, 0x00, 0x00, 0x00},
	{0x02, 0x00, 0x00, 0x00},
	{0x04, 0x00, 0x00, 0x00},
	{0x08, 0x00, 0x00, 0x00},
	{0x10, 0x00, 0x00, 0x00},
	{0x20, 0x00, 0x00, 0x00},
	{0x40, 0x00, 0x00, 0x00},
	{0x80, 0x00, 0x00, 0x00},
	{0x1b, 0x00, 0x00, 0x00},
	{0x36, 0x00, 0x00, 0x00},
};

const uint8_t m_sub_bytes[16][16] = {
	{0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
	{0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
	{0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
	{0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
	{0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
	{0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
	{0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
	{0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
	{0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
	{0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
	{0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
	{0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
	{0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
	{0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
	{0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
	{0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}, 
};

void encrypt_matrix(uint8_t m_estado[][4], uint8_t m_clave[][4]) {
	
	uint8_t count = 1;

	add_round_key(m_clave, m_estado);

	while(count < NUMBER_OF_ROUNDS) {
		key_expansion(m_clave, count);
		sub_bytes(m_estado);
		shift_rows(m_estado);
		mix_columns(m_estado);
		add_round_key(m_clave, m_estado);
		count++;
	}

	key_expansion(m_clave, NUMBER_OF_ROUNDS);
	sub_bytes(m_estado);
	shift_rows(m_estado);
	add_round_key(m_clave, m_estado);
	
	return;
}



void add_round_key(uint8_t m_clave[][4], uint8_t m_estado[][4]) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			m_estado[i][j] ^= m_clave[i][j];
		}
	}
	return;
}

void sub_bytes(uint8_t m_estado[][4]){
	uint8_t x = 0;
	uint8_t y = 0;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			x =  m_estado[i][j] >> 4;
			y =  m_estado[i][j] << 4;
			y =  y >> 4;
			m_estado[i][j] = m_sub_bytes[x][y];
		}
	}
	return;
}

void shift_rows(uint8_t m_estado[][4]){
	shift_row(m_estado[1], 1);
	shift_row(m_estado[2], 2);
	shift_row(m_estado[3], 3);
	return;
}


void shift_row(uint8_t* row, uint8_t n){

	if (n <= 0 || n > 3) return;

	uint8_t buffer[3] = {0, 0, 0};

	for (int i = 0; i < n; ++i) {
		buffer[i] = row[i];
	}

	for (int i = 0; i < 4 - n; ++i) {
		for (int j = n; j > 0; --j) {
			row[j + i - 1] = row[j + i];
		}
	}

	for (int i = 0; i < n; ++i) {
		row[4 - n + i] = buffer[i];
	}

	return;
}

void mix_columns(uint8_t m_estado[][4]) {
	
	uint8_t m_resultado[4][4] = {
		{0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x00},
	};

	for (int a = 0; a < 4; a++) {
    	// recorro filas
	    for (int i = 0; i < 4; i++) {
	        uint8_t suma = 0;
	        // para cada columna
	        for (int j = 0; j < 4; j++) {
	            suma = gadd(suma, gmul(m_constante[i][j], m_estado[j][a]));
	        }
	        m_resultado[i][a] = suma;
	    }
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m_estado[i][j] = m_resultado[i][j];
		}
	}

	return;
}

void key_expansion(uint8_t m_clave[][4], uint8_t round){

	// primera columna de la nueva clave

		// 1. tomo ultima columna clave actual
	uint8_t* colum_buffer = get_colum(m_clave, 3);

		// 2. rot word
	shift_row(colum_buffer, 1);

		// 3. sub bytes 
	sub_bytes_vector(colum_buffer);
	
		// 4. xor la primera columna de la clave actual
	uint8_t* colum_n = get_colum(m_clave, 0);
	xor_vector(colum_buffer, colum_n, 4);
	free(colum_n);

		// 5. xor con rcon[i]
	xor_vector(colum_buffer, m_rcon[round], 4);

		// 6. insert primera columna de la nueva clave
	insert_column(m_clave, colum_buffer, 0);

	// columnas restantes de la nueva clave

	for (int i = 1; i < 4; ++i) {
		colum_n = get_colum(m_clave, i);
		xor_vector(colum_n, colum_buffer, 4);
		insert_column(m_clave, colum_n, i);
		free(colum_buffer);
		colum_buffer = colum_n;
	}

	free(colum_buffer);
	return;
}

/* reserva memoria */
uint8_t* get_colum(uint8_t m_clave[][4], uint8_t colum) {

	uint8_t* colum_buffer = (uint8_t*) malloc (4 * sizeof(uint8_t));
	if (colum_buffer == NULL) exit(-1);
	
	for (int i = 0; i < 4; ++i) {
		colum_buffer[i] = m_clave[i][colum];
	}

	return colum_buffer;
}

void sub_bytes_vector(uint8_t* colum){
	uint8_t x = 0;
	uint8_t y = 0;

	for (int i = 0; i < 4; ++i) {
			x =  colum[i] >> 4;
			y =  colum[i] << 4;
			y =  y >> 4;
			colum[i] = m_sub_bytes[x][y];
	}

	return;
}

/* modifica vector_a */
void xor_vector(uint8_t* vector_a, const uint8_t* vector_b, uint8_t size) {
	for (int i = 0; i < size; ++i) {
		vector_a[i] = gadd(vector_a[i], vector_b[i]);
	}
	return;
}

void insert_column(uint8_t m_clave[][4], uint8_t* colum_buffer, uint8_t colum) {
	for (int i = 0; i < 4; ++i) {
		m_clave[i][colum] = colum_buffer[i];
	}
	return;
}