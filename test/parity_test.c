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

    if(1 < argc && 0 == strcmp("send", *(argv + 1))) {
        FILE* src = fopen("/home/link/workspace_git/ctree/main", "r");
        FILE* dst = fopen("/home/link/workspace_git/ctree/main_send", "w");

        fseek(src, 0, SEEK_END);
        long     sz   = ftell(src);
        uint8_t* buff = (uint8_t*)malloc(sz + 1);
        fseek(src, 0, SEEK_SET);
        fread(buff, 1, sz, src);
        parity_calc(Odd, buff, sz + 1, NULL);

        fwrite(buff, 1, sz + 1, dst);

        fclose(src);
        fclose(dst);
    }
    if(1 < argc && 0 == strcmp("recv", *(argv + 1))) {
        FILE* dst = fopen("/home/link/workspace_git/ctree/main_send", "r");
        fseek(dst, 0, SEEK_END);
        long     sz_1 = ftell(dst);
        uint8_t* buff = (uint8_t*)malloc(sz_1);
        fseek(dst, 0, SEEK_SET);
        fread(buff, 1, sz_1, dst);

        if(parity_check(Odd, buff, sz_1, NULL)) { printf("passed\n"); }

        fclose(dst);
    }

    return EXIT_SUCCESS;
}
