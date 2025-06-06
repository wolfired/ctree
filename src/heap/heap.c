#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heap.h"

Heap* heap__new(size_t bytes_per_element,
                size_t cap,
                bool (*swap_check)(void* element_child, void* element_parent),
                void (*swap)(void* element_a, void* element_b)) {
    Heap* thiz = (Heap*)malloc(sizeof(Heap));

    thiz->bytes_per_element = bytes_per_element;
    thiz->len               = 0;
    thiz->cap               = cap;
    thiz->swap_check        = swap_check;
    thiz->swap              = swap;
    thiz->bytes             = malloc(thiz->bytes_per_element * thiz->cap);

    return thiz;
}

void heap__del(Heap** p_thiz) {
    if(NULL == p_thiz || NULL == *p_thiz) { return; }

    free((*p_thiz)->bytes);
    (*p_thiz)->bytes = NULL;

    free((void*)*p_thiz);
    *p_thiz = NULL;
}

void heap_init(Heap* thiz, void* src_bytes, size_t src_len) {
    thiz->len = thiz->cap < src_len ? thiz->cap : src_len;
    memcpy(thiz->bytes, src_bytes, thiz->len * thiz->bytes_per_element);

    if(2 > thiz->len) { return; }

    size_t i = (thiz->len >> 1) - 1;

    do { heap_heapify_down(thiz, i); } while(0 < i--);
}

void heap_insert(Heap* thiz, void* element) {
    if(thiz->cap <= thiz->len) { return; }

    memcpy((uint8_t*)thiz->bytes + thiz->len * thiz->bytes_per_element,
           element,
           thiz->bytes_per_element);
    ++thiz->len;

    heap_heapify_up(thiz, thiz->len - 1);
}

bool heap_pop(Heap* thiz, void* move_out) {
    if(0 == thiz->len) { return false; }

    memcpy(move_out, thiz->bytes, thiz->bytes_per_element);
    memcpy(thiz->bytes,
           (uint8_t*)thiz->bytes + (thiz->len - 1) * thiz->bytes_per_element,
           thiz->bytes_per_element);
    --thiz->len;

    heap_heapify_down(thiz, 0);

    return true;
}

void* heap_top(Heap* thiz) {
    if(0 == thiz->len) { return NULL; }
    return thiz->bytes;
}

void heap_heapify_down(Heap* thiz, size_t i) {
    while(true) {
        size_t l = (i << 1) + 1;
        size_t r = (i << 1) + 2;
        size_t s = i;

        if(l < thiz->len &&
           thiz->swap_check((uint8_t*)thiz->bytes + l * thiz->bytes_per_element,
                            (uint8_t*)thiz->bytes + s * thiz->bytes_per_element)) {
            s = l;
        }
        if(r < thiz->len &&
           thiz->swap_check((uint8_t*)thiz->bytes + r * thiz->bytes_per_element,
                            (uint8_t*)thiz->bytes + s * thiz->bytes_per_element)) {
            s = r;
        }

        if(s == i) { break; }

        thiz->swap((uint8_t*)thiz->bytes + i * thiz->bytes_per_element,
                   (uint8_t*)thiz->bytes + s * thiz->bytes_per_element);

        i = s;
    }
}

void heap_heapify_up(Heap* thiz, size_t i) {
    while(true) {
        if(0 == i) { break; }
        size_t p = (i - 1) >> 1;

        if(!thiz->swap_check((uint8_t*)thiz->bytes + i * thiz->bytes_per_element,
                             (uint8_t*)thiz->bytes + p * thiz->bytes_per_element)) {
            break;
        }

        thiz->swap((uint8_t*)thiz->bytes + i * thiz->bytes_per_element,
                   (uint8_t*)thiz->bytes + p * thiz->bytes_per_element);

        i = p;
    }
}

void heap_info(Heap* thiz) {
    printf("Heap { bytes_per_element: %zd, len: %zd, cap: %zd }\n",
           thiz->bytes_per_element,
           thiz->len,
           thiz->cap);
}
