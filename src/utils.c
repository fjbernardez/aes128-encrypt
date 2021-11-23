#include "headers.h"

void show_matrix(char* label, uint8_t m_resultado[][4]){
	printf("%s",label);
	printf("\n");
	for (int i = 0; i < 4; i++) {
		printf("\t");
		for (int j = 0; j < 4; j++) {
			printf("%02x ", m_resultado[i][j]);
		}
		printf("\n");
	}
}

void show_vector(char* label, uint8_t * v_resultado, uint8_t size){
	printf("%s",label);
	printf("\n");
		printf("\t");
		for (int i = 0; i < size; i++) {
			printf("%02x ", v_resultado[i]);
		}
		printf("\n");
}

void char_to_bin(uint8_t val) {
    char buffer[9];
	buffer[8] = '\0';
    for (int i = 7; i >= 0; i--) {
        buffer[i] = (val & 1) + '0';
        val >>= 1;
    }
	printf("%s", buffer);
    return;
}