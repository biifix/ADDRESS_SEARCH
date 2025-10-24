#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

/*create and retunr a new empty list*/
list_t *make_empty_list() {

    list_t *list = malloc(sizeof(list_t));
    assert(list != NULL);

    list->head = NULL;
    list->foot = NULL;

    return list;
}

int is_empty_list(list_t *list) {
    assert(list != NULL);
    return (list->head == NULL && list->foot == NULL);
}


/*insert a new record at foot of the list*/
list_t *insert_at_foot(list_t *list, data_t data) {
    assert(list != NULL);

    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    assert(new_node != NULL);

    new_node->data = data;
    new_node->next = NULL;

    if (is_empty_list(list)) {
        list->head = new_node;
        list->foot = new_node;
    } else {
        list->foot->next = new_node;
        list->foot = new_node;
    }

    return list;
}

void free_list(list_t *list) {
    assert(list != NULL);

    node_t *curr = list->head;
    node_t *next;

    while (curr != NULL) {
        next = curr->next;

        /* Free the record stored in this node. */
        free_record(curr->data);

        /* Free the node itself. */
        free(curr);

        curr = next;
    }

    free(list);
}
