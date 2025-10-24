#ifndef LIST_H
#define LIST_H


#include "record.h"
#include <stdlib.h>
#include <string.h>

typedef record_t* data_t;
typedef struct node node_t;

struct node {
    data_t data;
    node_t *next;
};

typedef struct {
    node_t *head;
    node_t *foot;
} list_t;

list_t *make_empty_list();
int is_empty_list(list_t *list);
void free_list(list_t *list);
list_t *insert_at_foot(list_t *list, data_t data);

#endif

