#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sort.h>

bool swap_if(void const* left, void const* right) {
    char const* left_ptr  = (char*)left;
    char const* right_ptr = (char*)right;
    return *left_ptr > *right_ptr;
}

void sort_str() {
    char str0[] = "784159620354126938710215897450";
    bubble_sort(str0, sizeof(char), strlen(str0), swap_if);
    printf("%16s -> %s\n", "bubble_sort", str0);

    char str1[] = "784159620354126938710215897450";
    insert_sort(str1, sizeof(char), strlen(str1), swap_if);
    printf("%16s -> %s -> %16s\n",
           "insert_sort",
           str1,
           0 == strcmp(str0, str1) ? "equ bubble_sort" : "failed");

    char str2[] = "784159620354126938710215897450";
    selection_sort(str2, sizeof(char), strlen(str2), swap_if);
    printf("%16s -> %s -> %16s\n",
           "selection_sort",
           str2,
           0 == strcmp(str0, str2) ? "equ bubble_sort" : "failed");

    char str3[] = "784159620354126938710215897450";
    quick_sort(str3, sizeof(char), strlen(str3), swap_if);
    printf("%16s -> %s -> %16s\n",
           "quick_sort",
           str3,
           0 == strcmp(str0, str3) ? "equ bubble_sort" : "failed");

    char str4[] = "784159620354126938710215897450";
    merge_sort(str4, sizeof(char), strlen(str4), swap_if);
    printf("%16s -> %s -> %16s\n",
           "merge_sort",
           str4,
           0 == strcmp(str0, str4) ? "equ bubble_sort" : "failed");
}

void sort_uint16_t() {
    size_t const n = 10;

    uint16_t arr0[] = {0, 2, 5, 4, 7, 8, 9, 6, 3, 1};
    bubble_sort(arr0, sizeof(uint16_t), n, swap_if);
    printf("%16s -> [", "bubble_sort", arr0);
    for(size_t i = 0; i < n; i++) { printf("%d, ", arr0[i]); }
    printf("]\n");

    uint16_t arr1[] = {0, 2, 5, 4, 7, 8, 9, 6, 3, 1};
    insert_sort(arr1, sizeof(uint16_t), n, swap_if);
    printf("%16s -> [", "insert_sort", arr1);
    for(size_t i = 0; i < n; i++) { printf("%d, ", arr1[i]); }
    printf("]\n");

    uint16_t arr2[] = {0, 2, 5, 4, 7, 8, 9, 6, 3, 1};
    selection_sort(arr2, sizeof(uint16_t), n, swap_if);
    printf("%16s -> [", "selection_sort", arr2);
    for(size_t i = 0; i < n; i++) { printf("%d, ", arr2[i]); }
    printf("]\n");

    uint16_t arr3[] = {0, 2, 5, 4, 7, 8, 9, 6, 3, 1};
    quick_sort(arr3, sizeof(uint16_t), n, swap_if);
    printf("%16s -> [", "quick_sort", arr3);
    for(size_t i = 0; i < n; i++) { printf("%d, ", arr3[i]); }
    printf("]\n");

    uint16_t arr4[] = {0, 2, 5, 4, 7, 8, 9, 6, 3, 1};
    merge_sort(arr4, sizeof(uint16_t), n, swap_if);
    printf("%16s -> [", "merge_sort", arr4);
    for(size_t i = 0; i < n; i++) { printf("%d, ", arr4[i]); }
    printf("]\n");
}

int main(int argc, char** argv) {
    sort_str();
    sort_uint16_t();

    return EXIT_SUCCESS;
}
