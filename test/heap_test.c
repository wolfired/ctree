#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdalign.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <heap.h>

bool test_big(void* element_child, void* element_parent) {
    int32_t* p_element_child  = (int32_t*)element_child;
    int32_t* p_element_parent = (int32_t*)element_parent;

    return *p_element_child > *p_element_parent;
}

void test_swap(void* element_a, void* element_b) {
    int32_t* p_element_a = (int32_t*)element_a;
    int32_t* p_element_b = (int32_t*)element_b;

    int32_t tmp  = *p_element_a;
    *p_element_a = *p_element_b;
    *p_element_b = tmp;
}

int main(int argc, char** argv) {
    int32_t arr[] = {
        9, 1, 0, 3, 8, 4, 5, 6, 7, 2, 9, 1, 0, 3, 8, 4, 5, 6, 7, 2,
        9, 1, 0, 3, 8, 4, 5, 6, 7, 2, 9, 1, 0, 3, 8, 4, 5, 6, 7,
    };
    Heap* ptr_heap = heap__new(sizeof(int32_t), 64, test_big, test_swap);
    heap_init(ptr_heap, arr, 39);
    heap_info(ptr_heap);

    printf("top is %d\n", *(int32_t*)heap_top(ptr_heap));

    heap_insert(ptr_heap, &(int32_t){2});
    heap_info(ptr_heap);

    int32_t out;
    while(heap_pop(ptr_heap, &out)) { printf("%zd, ", out); }
    heap_info(ptr_heap);
    heap__del(&ptr_heap);

    return EXIT_SUCCESS;
}
