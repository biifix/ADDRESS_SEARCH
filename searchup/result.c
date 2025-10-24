#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "result.h"

/* allocate and initialise given query key*/
result_t *create_result(char *key) {
    result_t *result = malloc(sizeof(result_t));
    assert(result != NULL);

    result -> key = strdup(key);
    result -> num_matches = 0;
    result -> node_accesses = 0;
    result -> bit_cmps = 0;
    result -> str_cmps = 0;
    result->match = make_empty_list();


    return result;

}

/* print the result to stdout */
void print_stdout_result(result_t *result) {
    assert(result != NULL);
    printf("%s --> %d records found - comparisons: b%d n%d s%d\n", result->key, result->num_matches, 
           result->bit_cmps, result->node_accesses, result->str_cmps);
}

// print the result to the given output file
void print_file_result(result_t *result, FILE *out) {
    assert(result != NULL);
    assert(out != NULL);
    // Summary line should only go to stdout, not to file
    // The file only contains the query and matching records (printed in dict.c)
}

/* free the result memory */
void free_result(result_t *result) {
    if (result != NULL) {
        free(result->key);
        free(result);
    }
}

