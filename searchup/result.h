#ifndef RESULT_H
#define RESULT_H
#include "list.h"
#include <stdio.h>



typedef struct {
    char *key;
    int num_matches;
    int bit_cmps;
    int str_cmps;
    int node_accesses;

    list_t* match;

} result_t;

result_t *create_result(char *key);
void print_stdout_result(result_t *result);
void print_file_result(result_t *result, FILE *out);
void free_result(result_t *result);


#endif