#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdint.h>

typedef struct _HuffmanNode {
    struct _HuffmanNode* parent;
    struct _HuffmanNode* left;
    struct _HuffmanNode* right;
    uint8_t              data;
    uint32_t             freq;
} HuffmanNode;

HuffmanNode* huffman_node__new();
void         huffman_node__del(HuffmanNode** p_thiz);

typedef struct _HuffmanTree {
    HuffmanNode* root;
} HuffmanTree;

HuffmanTree* huffman_tree__new();
void         huffman_tree__del(HuffmanTree** p_thiz);

void huffman_tree_init(HuffmanTree* thiz,
                       void*        src_bytes,
                       size_t       src_bytes_size);

#endif
