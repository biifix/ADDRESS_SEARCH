#ifndef PTRIE_H
#define PTRIE_H

#include "list.h"
#include "result.h"
#include <stdio.h>

typedef struct node_p pnode_t;
typedef record_t* data_t;

struct node_p {
    int prefix_bit;
    char* prefix;
    pnode_t* left;
    pnode_t* right;
    list_t* data_list;
    int num_data;
    int is_leaf;
};

typedef struct {
    pnode_t* root;
} ptrie_t;

ptrie_t* make_empty_ptrie();
void insert_ptrie(ptrie_t* tree, data_t data);
void search_ptrie(ptrie_t* tree, char* key, result_t* result);
void free_ptrie(ptrie_t* tree);

int editDistance(char *str1, char *str2, int n, int m);
int min(int a, int b, int c);

#endif 

