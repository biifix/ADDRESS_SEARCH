#ifndef DICT_H
#define DICT_H


#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "result.h"
#include "ptrie.h"

#define MAX_LINE_LEN 511

typedef ptrie_t dict_t;

dict_t *create_dict(FILE *file);
result_t* search_dict(dict_t *dict, char *key, FILE *out);
void free_dict(dict_t *dict);


#endif
