#include "parity.h"

static uint8_t ones_count_in_byte[] = {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, //
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, //
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, //
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, //
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, //
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, //
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, //
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, //
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, //
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, //
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, //
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, //
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, //
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, //
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, //
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, //
};

bool parity_check(Parity         parity,
                  uint8_t const* bytes,
                  size_t         bytes_count,
                  uint8_t const* parity_bit_lsb) {
    if(NULL == bytes || 0 == bytes_count) { return false; }

    if(NULL == parity_bit_lsb) { parity_bit_lsb = bytes + bytes_count - 1; }

    if(bytes <= parity_bit_lsb && parity_bit_lsb < bytes + bytes_count &&
       1 == bytes_count) {
        return false;
    }

    size_t count = 0;
    for(size_t i = 0; i < bytes_count; ++i) {
        count += ones_count_in_byte[bytes[i]];
    }

    if(parity_bit_lsb < bytes || bytes + bytes_count <= parity_bit_lsb) {
        count += ones_count_in_byte[*parity_bit_lsb & 0b00000001];
    }

    return (size_t)parity == count % 2;
}

void parity_calc(Parity         parity,
                 uint8_t const* bytes,
                 size_t         bytes_count,
                 uint8_t*       parity_bit_lsb) {
    if(NULL == bytes || 0 == bytes_count) { return; }

    if(NULL == parity_bit_lsb) {
        parity_bit_lsb = (uint8_t*)bytes + bytes_count - 1;
    }

    if(bytes <= parity_bit_lsb && parity_bit_lsb < bytes + bytes_count &&
       1 == bytes_count) {
        return;
    }

    *parity_bit_lsb = 0;

    size_t count = 0;
    for(size_t i = 0; i < bytes_count; ++i) {
        count += ones_count_in_byte[bytes[i]];
    }

    *parity_bit_lsb = Even == parity ? count % 2 : 1 >> count % 2;
}
