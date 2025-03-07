#include <string.h>

#include "sort.h"

static void swap(void* ex, void* lo, void* hi, size_t bytes_per_element) {
    memcpy(ex, lo, bytes_per_element);
    memcpy(lo, hi, bytes_per_element);
    memcpy(hi, ex, bytes_per_element);
}

void bubble_sort(void*  data,
                 size_t bytes_per_element,
                 size_t element_count,
                 SwapIf swap_if) {
    void* ex = malloc(bytes_per_element);

    for(size_t left = 1; left < element_count; ++left) {
        bool sorted = true;
        for(size_t right = element_count - 1; right >= left; --right) {
            if(swap_if(data + bytes_per_element * (right - 1),
                       data + bytes_per_element * right)) {
                swap(ex,
                     data + bytes_per_element * (right - 1),
                     data + bytes_per_element * right,
                     bytes_per_element);
                sorted = false;
            }
        }
        if(sorted) { break; }
    }

    free(ex);
    ex = NULL;
}

void insert_sort(void*  data,
                 size_t bytes_per_element,
                 size_t element_count,
                 SwapIf swap_if) {
    void* marked_value = malloc(bytes_per_element);

    for(size_t right = 1; right < element_count; ++right) {
        memcpy(
            marked_value, data + bytes_per_element * right, bytes_per_element);

        size_t left = right;

        for(; left > 0 &&
              swap_if(data + bytes_per_element * (left - 1), marked_value);
            --left) {
            memcpy(data + bytes_per_element * left,
                   data + bytes_per_element * (left - 1),
                   bytes_per_element);
        }

        if(left != right)
            memcpy(data + bytes_per_element * left,
                   marked_value,
                   bytes_per_element);
    }

    free(marked_value);
    marked_value = NULL;
}

void selection_sort(void*  data,
                    size_t bytes_per_element,
                    size_t element_count,
                    SwapIf swap_if) {
    void* ex = malloc(bytes_per_element);

    for(size_t left = 1; left < element_count; ++left) {
        size_t marked_index = left - 1;
        for(size_t right = left; right < element_count; ++right) {
            if(swap_if(data + bytes_per_element * marked_index,
                       data + bytes_per_element * right)) {
                marked_index = right;
            }
        }
        if(left - 1 != marked_index)
            swap(ex,
                 data + bytes_per_element * (left - 1),
                 data + bytes_per_element * marked_index,
                 bytes_per_element);

        free(ex);
        ex = NULL;
    }
}