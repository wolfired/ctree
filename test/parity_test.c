#include <assert.h>
#include <inttypes.h>
#include <locale.h>
#include <math.h>
#include <stdalign.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <parity.h>

int main(int argc, char** argv) {
    uint8_t data[] = {0b10101010, 0b00000000};

    parity_calc(Odd, data, 1, &data[1]);

    printf("%08b %08b\n", data[0], data[1]);

    if(parity_check(Odd, data, 1, &data[1])) { printf("check passed\n"); }

    return EXIT_SUCCESS;
}
