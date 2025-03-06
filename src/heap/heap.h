#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>

typedef struct _Heap {
    void*  bytes;
    size_t bytes_per_element;
    size_t len;
    size_t cap;
    bool (*swap_check)(void* element_child, void* element_parent);
    void (*swap)(void* element_a, void* element_b);
} Heap;

Heap* heap__new(size_t bytes_per_element,
                size_t cap,
                bool (*swap_check)(void* element_child, void* element_parent),
                void (*swap)(void* element_a, void* element_b));
void  heap__del(Heap** p_thiz);

void  heap_init(Heap* thiz, void* src_bytes, size_t src_len);
void  heap_insert(Heap* thiz, void* element);
bool  heap_pop(Heap* thiz, void* move_out);
void* heap_top(Heap* thiz);
void  heap_heapify_down(Heap* thiz, size_t i);
void  heap_heapify_up(Heap* thiz, size_t i);
void  heap_info(Heap* thiz);

#endif
