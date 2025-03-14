#ifndef PARITY_H
#define PARITY_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum _Parity {
    Even = 0,
    Odd  = 1,
} Parity;

bool parity_check(Parity         parity,
                  uint8_t const* bytes,
                  size_t         bytes_count,
                  uint8_t const* parity_bit_lsb);

void parity_calc(Parity         parity,
                 uint8_t const* bytes,
                 size_t         bytes_count,
                 uint8_t*       parity_bit_lsb);

#endif
