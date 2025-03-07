#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sort.h>

bool swap_if(void const* lo, void const* hi) {
    char const* p_lo = (char*)lo;
    char const* p_hi = (char*)hi;
    return *p_lo > *p_hi;
}

int main(int argc, char** argv) {
    int const               a = 0;
    int const* const        b = &a;
    int const* const* const c = &b;

    char str[] = "78415962035412693871021589745";
    quick_sort(str, sizeof(char), strlen(str), swap_if);
    printf("%s\n", str);

    return EXIT_SUCCESS;
}