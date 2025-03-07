#ifndef SORT_H
#define SORT_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef bool (*SwapIf)(void* lo, void* hi);

void bubble_sort(void*  data,
                 size_t bytes_per_element,
                 size_t element_count,
                 SwapIf swap_if);

void insert_sort(void*  data,
                 size_t bytes_per_element,
                 size_t element_count,
                 SwapIf swap_if);

void selection_sort(void*  data,
                    size_t bytes_per_element,
                    size_t element_count,
                    SwapIf swap_if);

#endif