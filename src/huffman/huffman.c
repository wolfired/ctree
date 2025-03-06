#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FREQS_COUNT 256

#include "heap.h"

#include "huffman.h"

static bool swap_check(void* element_child, void* element_parent) {
    HuffmanNode** p_element_child  = (HuffmanNode**)element_child;
    HuffmanNode** p_element_parent = (HuffmanNode**)element_parent;

    return (*p_element_child)->freq < (*p_element_parent)->freq;
}

static void swap(void* element_a, void* element_b) {
    HuffmanNode** p_element_a = (HuffmanNode**)element_a;
    HuffmanNode** p_element_b = (HuffmanNode**)element_b;

    HuffmanNode* tmp = *p_element_a;
    *p_element_a     = *p_element_b;
    *p_element_b     = tmp;
}

static void huffman_node_preorder(HuffmanNode* root,
                                  void (*cb)(HuffmanNode* node)) {
    cb(root);
    if(NULL != root && NULL != root->left) {
        huffman_node_preorder(root->left, cb);
    }
    if(NULL != root && NULL != root->right) {
        huffman_node_preorder(root->right, cb);
    }
}

static void huffman_node_inorder(HuffmanNode* root,
                                 void (*cb)(HuffmanNode* node)) {
    if(NULL != root && NULL != root->left) {
        huffman_node_inorder(root->left, cb);
    }
    cb(root);
    if(NULL != root && NULL != root->right) {
        huffman_node_inorder(root->right, cb);
    }
}

static void huffman_node_postorder(HuffmanNode* root,
                                   void (*cb)(HuffmanNode* node)) {
    if(NULL != root && NULL != root->left) {
        huffman_node_postorder(root->left, cb);
    }
    if(NULL != root && NULL != root->right) {
        huffman_node_postorder(root->right, cb);
    }
    cb(root);
}

static void huffman_tree_del_node(HuffmanNode* node) {
    if(NULL == node) { return; }

    huffman_node__del(&node);
}

HuffmanNode* huffman_node__new() {
    HuffmanNode* thiz = calloc(1, sizeof(HuffmanNode));
    return thiz;
}
void huffman_node__del(HuffmanNode** p_thiz) {
    if(NULL == p_thiz || NULL == *p_thiz) { return; }

    free((void*)*p_thiz);
    *p_thiz = NULL;
}

HuffmanTree* huffman_tree__new() {
    HuffmanTree* thiz = malloc(sizeof(HuffmanTree));
    thiz->root        = NULL;
    return thiz;
}

void huffman_tree__del(HuffmanTree** p_thiz) {
    if(NULL == p_thiz || NULL == *p_thiz) { return; }

    huffman_node_postorder((*p_thiz)->root, huffman_tree_del_node);

    free((void*)*p_thiz);
    *p_thiz = NULL;
}

void huffman_tree_init(HuffmanTree* thiz,
                       void*        src_bytes,
                       size_t       src_bytes_size) {
    uint32_t freqs[FREQS_COUNT] = {};
    memset(freqs, 0, FREQS_COUNT * 4);

    for(size_t i = 0; i < src_bytes_size; ++i) {
        ++freqs[((uint8_t*)src_bytes)[i]];
    }

    Heap* heap = heap__new(sizeof(HuffmanNode*), FREQS_COUNT, swap_check, swap);

    for(size_t i = 0; i < FREQS_COUNT; i++) {
        if(0 != freqs[i]) {
            printf("%c -> %zd\n", (char)i, freqs[i]);
            HuffmanNode* h = huffman_node__new();
            h->data        = i;
            h->freq        = freqs[i];
            heap_insert(heap, &h);
        }
    }

    while(1 < heap->len) {
        HuffmanNode *l, *r, *p = huffman_node__new();
        heap_pop(heap, &l);
        heap_pop(heap, &r);
        p->left  = l;
        p->right = r;
        p->freq  = l->freq + r->freq;
        heap_insert(heap, &p);
    }

    heap_pop(heap, &thiz->root);
    heap__del(&heap);
}

void dfs_pre(HuffmanNode* r, void (*cb)(HuffmanNode* n, int8_t c), int8_t c) {
    cb(r, c);
    if(NULL != r->left) { dfs_pre(r->left, cb, 0); }
    if(NULL != r->right) { dfs_pre(r->right, cb, 1); }
}
