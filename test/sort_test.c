#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sort.h>

bool swap_if(void* lo, void* hi) {
    char* p_lo = (char*)lo;
    char* p_hi = (char*)hi;
    return *p_lo > *p_hi;
}

int main(int argc, char** argv) {
    char str[] = "7841596203";
    insert_sort(str, sizeof(char), strlen(str), swap_if);
    printf("%s\n", str);

    return EXIT_SUCCESS;
}