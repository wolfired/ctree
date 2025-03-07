#include <stdbool.h>
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
    char str0[] = "78415962035412693871021589745";
    merge_sort(str0, sizeof(char), strlen(str0), swap_if);
    printf("%s\n", str0);

    char str1[] = "78415962035412693871021589745";
    bubble_sort(str1, sizeof(char), strlen(str1), swap_if);
    printf("%s\n", str1);

    printf("%s\n", 0 == strcmp(str0, str1) ? "sorded" : "not sorded");

    return EXIT_SUCCESS;
}
