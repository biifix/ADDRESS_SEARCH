#include "dict.h"
#include "bit.h"
#include <assert.h>
#include "ptrie.h"

dict_t *create_dict(FILE *file) {
    assert(file != NULL);

    dict_t* dict = make_empty_ptrie(); //TODO change to using ptrie
    char line_temp[MAX_LINE_LEN + 1]; // buffer for reading lines in CSV


    // ignore header line
    fgets(line_temp, MAX_LINE_LEN + 1, file);

    // read each line from the file and create a record as a node in the linked list
    while (fgets(line_temp, sizeof(line_temp), file) != NULL) {

        record_t *record = create_record(line_temp);


        // add to patricia trie dictionary
        //TODO: change to ptrie insert
        insert_ptrie(dict, record);
        
    }

    return dict;

}

// free the dictionary and all its records
void free_dict(dict_t *dict) {
    //TODO: free ptrie
    free_ptrie(dict);
}


result_t* search_dict(dict_t *dict, char *key, FILE *out) {
    assert(dict != NULL);
    assert(key != NULL);
    assert(out != NULL);

    result_t *result = create_result(key);

    result->bit_cmps = 0;
    result->node_accesses = 0;
    result->str_cmps = 0;
    result->num_matches = 0;
  

    // print the query prefix so that mathcing records are to be appended on the same line
    fprintf(out, "%s\n", key);

    //search the ptrie for the key
    search_ptrie(dict, key, result);
    // use search ptrie function
    //TODO: change to ptrie search: store results in result struct
    if (result->num_matches > 0 && result->match != NULL) {
        node_t *curr = result->match->head;
        while (curr != NULL) {
            print_record(curr->data, out);
            curr = curr->next;
        }
    }
    return result;
}
