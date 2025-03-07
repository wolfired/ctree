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
    bubble_sort(str0, sizeof(char), strlen(str0), swap_if);
    printf("%16s -> %s\n", "bubble_sort", str0);

    char str1[] = "78415962035412693871021589745";
    insert_sort(str1, sizeof(char), strlen(str1), swap_if);
    printf("%16s -> %s -> %16s\n",
           "insert_sort",
           str1,
           0 == strcmp(str0, str1) ? "equ bubble_sort" : "failed");

    char str2[] = "78415962035412693871021589745";
    selection_sort(str2, sizeof(char), strlen(str2), swap_if);
    printf("%16s -> %s -> %16s\n",
           "selection_sort",
           str2,
           0 == strcmp(str0, str2) ? "equ bubble_sort" : "failed");

    char str3[] = "78415962035412693871021589745";
    quick_sort(str3, sizeof(char), strlen(str3), swap_if);
    printf("%16s -> %s -> %16s\n",
           "quick_sort",
           str3,
           0 == strcmp(str0, str3) ? "equ bubble_sort" : "failed");

    char str4[] = "78415962035412693871021589745";
    merge_sort(str4, sizeof(char), strlen(str4), swap_if);
    printf("%16s -> %s -> %16s\n",
           "merge_sort",
           str4,
           0 == strcmp(str0, str4) ? "equ bubble_sort" : "failed");

    return EXIT_SUCCESS;
}
