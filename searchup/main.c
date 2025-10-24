#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dict.h"

#define STAGE_ONE 1
#define STAGE_TWO 2


int main(int argc, char **argv) {

    // Open the input CSV file and output CSV file
    FILE *in_file =fopen(argv[2], "r");
    assert(in_file != NULL);
    FILE *out_file = fopen(argv[3], "w");
    assert(out_file != NULL);


    // create the dictionary (linked-list of records) from the input file
    dict_t *dict = create_dict(in_file);

    // temporary array to hold the query string
    char query_temp[MAX_FIELD_LEN + 1];

    while(fgets(query_temp, sizeof(query_temp), stdin) != NULL) {
        // remove the newline character from the query string
        size_t len = strlen(query_temp);
        if (len > 0 && query_temp[len - 1] == '\n') {
            query_temp[len - 1] = '\0';
        }

        // search the dictionary for the query and print the result
        result_t *result = search_dict(dict, query_temp, out_file);

        // if result - match == null then no match found, else print all record

        // print result to the output file
        print_stdout_result(result);
        print_file_result(result, out_file);
        free_result(result);
    }

    fclose(in_file);
    fclose(out_file);
    free_dict(dict);

    return 0;
}