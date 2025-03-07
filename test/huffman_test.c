#include <assert.h>
#include <inttypes.h>
#include <locale.h>
#include <math.h>
#include <stdalign.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <huffman.h>

int main(int argc, char** argv) {
    HuffmanTree* tree = huffman_tree__new();
    huffman_tree_init(tree, "hello", 5);
    huffman_tree__del(&tree);

    return EXIT_SUCCESS;
}
