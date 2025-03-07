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
    if(0 == bytes_per_element || 0 == element_count) { return; }

    void* ex = malloc(bytes_per_element);

    if(NULL == ex) { return; }

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
    if(0 == bytes_per_element || 0 == element_count) { return; }

    void* marked_value = malloc(bytes_per_element);

    if(NULL == marked_value) { return; }

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
    if(0 == bytes_per_element || 0 == element_count) { return; }

    void* ex = malloc(bytes_per_element);

    if(NULL == ex) { return; }

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

void quick_sort(void*  data,
                size_t bytes_per_element,
                size_t element_count,
                SwapIf swap_if) {
    if(0 == bytes_per_element || 0 == element_count) { return; }

    if(8 >= element_count) {
        insert_sort(data, bytes_per_element, element_count, swap_if);
        return;
    }

    void* ex = malloc(bytes_per_element);

    if(NULL == ex) { return; }

    swap(ex,
         data + bytes_per_element * 1,
         data + bytes_per_element * (element_count / 2),
         bytes_per_element);
    swap(ex,
         data + bytes_per_element * 2,
         data + bytes_per_element * (element_count - 1),
         bytes_per_element);
    insert_sort(data, bytes_per_element, 3, swap_if);
    swap(ex,
         data + bytes_per_element * 2,
         data + bytes_per_element * (element_count - 1),
         bytes_per_element);

    size_t left  = 2;
    size_t right = element_count - 2;

    while(left <= right) {
        while(left <= right) {
            if(!swap_if(data + bytes_per_element * 1,
                        data + bytes_per_element * left)) {
                break;
            }
            ++left;
        }
        while(left <= right) {
            if(swap_if(data + bytes_per_element * 1,
                       data + bytes_per_element * right)) {
                break;
            }
            --right;
        }
        if(left < right) {
            swap(ex,
                 data + bytes_per_element * left,
                 data + bytes_per_element * right,
                 bytes_per_element);
            ++left;
            --right;
        }
    }
    swap(ex,
         data + bytes_per_element * 1,
         data + bytes_per_element * right,
         bytes_per_element);

    quick_sort(data, bytes_per_element, right, swap_if);
    quick_sort(data + bytes_per_element * left,
               bytes_per_element,
               element_count - left,
               swap_if);

    free(ex);
    ex = NULL;
}

static void merge(void*  dest,
                  void*  left,
                  size_t left_sz,
                  void*  right,
                  size_t right_sz,
                  size_t bytes_per_element,
                  SwapIf swap_if) {
    size_t i = 0, j = 0, k = 0;
    for(; i < left_sz && j < right_sz; ++k) {
        if(!swap_if(left + bytes_per_element * i,
                    right + bytes_per_element * j)) {
            memcpy(dest + bytes_per_element * k,
                   left + bytes_per_element * i,
                   bytes_per_element);
            ++i;
        } else {
            memcpy(dest + bytes_per_element * k,
                   right + bytes_per_element * j,
                   bytes_per_element);
            ++j;
        }
    }

    if(i < left_sz) {
        memcpy(dest + bytes_per_element * k,
               left + bytes_per_element * i,
               bytes_per_element * (left_sz - i));
    } else if(j < right_sz) {
        memcpy(dest + bytes_per_element * k,
               right + bytes_per_element * j,
               bytes_per_element * (right_sz - j));
    }
}

static void merge_sort_pri(void*  data,
                           void*  temp,
                           size_t bytes_per_element,
                           size_t element_count,
                           SwapIf swap_if) {
    if(0 == bytes_per_element || 0 == element_count) { return; }

    if(8 >= element_count) {
        insert_sort(data, bytes_per_element, element_count, swap_if);
        return;
    }

    size_t half = element_count / 2;

    merge_sort_pri(data, temp, bytes_per_element, half, swap_if);
    merge_sort_pri(data + bytes_per_element * half,
                   temp + bytes_per_element * half,
                   bytes_per_element,
                   element_count - half,
                   swap_if);

    merge(temp,
          data,
          half,
          data + bytes_per_element * half,
          element_count - half,
          bytes_per_element,
          swap_if);

    memcpy(data, temp, element_count);
}

void merge_sort(void*  data,
                size_t bytes_per_element,
                size_t element_count,
                SwapIf swap_if) {
    if(0 == bytes_per_element || 0 == element_count) { return; }

    if(8 >= element_count) {
        insert_sort(data, bytes_per_element, element_count, swap_if);
        return;
    }

    uint8_t* temp = malloc(bytes_per_element * element_count);

    if(NULL == temp) { return; }

    merge_sort_pri(data, temp, bytes_per_element, element_count, swap_if);
    free(temp);
    temp = NULL;
}
