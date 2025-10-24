#include "ptrie.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include "bit.h"

int editDistance(char *str1, char *str2, int n, int m);
int min(int a, int b, int c);

pnode_t* in_ptrie(ptrie_t* tree, char* key, result_t* result , int *found) {
    pnode_t* current = tree->root;
    if (current == NULL) {
        return NULL;
    }
    
    int diff_index = 0;
    int diff_bit = BITS_PER_BYTE * (strlen(key) + 1);
    char* diff_stem = createStem(key, 0, diff_bit);
    int bit_isMatching(pnode_t* node, char* stem, int numBits, result_t* result);

    

    while (current != NULL) {
        // Count every node we visit during traversal
        if (result) {
            result->node_accesses++;
        }

        int matching = bit_isMatching(current, diff_stem, diff_bit, result);

        // compare and check if all bit are matching
        if (matching) {
            // all bits are matching
            if (current -> prefix_bit == diff_bit) {
                *found = 1;
                free(diff_stem);
                return current;
            }


            // continue down the tree
            diff_index += current->prefix_bit;
            diff_bit -= current->prefix_bit;
            free(diff_stem);
            diff_stem = createStem(key, diff_index, diff_bit);
            
            int bit = getBit(diff_stem, 0);
            if (bit == 0) {
                current = current->left;
            } else {
                current = current->right;
            }
            continue;
            // mismatching bit found
        } else {
            *found = 0;
            free(diff_stem);
            return current;
        }
    }
    *found = 0;
    free(diff_stem);
    return NULL;
}


ptrie_t* make_empty_ptrie() {
    ptrie_t* tree = malloc(sizeof(ptrie_t));
    assert(tree != NULL);
    tree->root = NULL;
    return tree;
}

pnode_t* make_pnode(int prefix_bit, char* prefix) {
    pnode_t* node = malloc(sizeof(pnode_t));
    assert(node != NULL);

    node->prefix_bit = prefix_bit;
    node->prefix = prefix;
    node->left = NULL;
    node->right = NULL;
    node->data_list = make_empty_list();
    node->num_data = 0;        
    node->is_leaf  = 0;  

    return node;
}

int bit_isMatching(pnode_t* node, char* stem, int numBits, result_t* result) {
    assert(node != NULL && stem != NULL && numBits >= 0);
    
    for (int i = 0; i < node->prefix_bit && i < numBits; i++) {
        if (result != NULL) {
            result->bit_cmps++;
        }
        int bit1 = getBit(node->prefix, i);
        int bit2 = getBit(stem, i);
        if (bit1 != bit2) {
            return 0;
        }
    }
    return 1;
}

// insert a new record into the ptrie
void insert_ptrie(ptrie_t* tree, data_t data) {
    pnode_t* current = tree->root;
    if (current == NULL) {
        pnode_t* leaf = malloc(sizeof(pnode_t));
        assert(leaf);
        // initialize leaf node
        leaf->prefix_bit = BITS_PER_BYTE * (strlen(data->EZI_ADD) + 1);
        leaf->prefix = createStem(data->EZI_ADD, 0, leaf->prefix_bit);
        leaf->left = NULL;
        leaf->right = NULL;
        leaf->data_list = make_empty_list();
        insert_at_foot(leaf->data_list, data);
        leaf->num_data = 1;
        leaf->is_leaf = 1;

        tree->root = leaf;
        return;
    }

    char *key = data->EZI_ADD;
    int diff_index = 0;
    int diff_bit = BITS_PER_BYTE * (int)(strlen(key) + 1);
    char* diff_stem = createStem(key, 0, diff_bit);
    

    while (current != NULL) {
        // compare and check if all bit are matching
        if (bit_isMatching(current, diff_stem, diff_bit, NULL)) {

            if (current -> prefix_bit == diff_bit) {
                // all bits are matching and we are at leaf node
                insert_at_foot(current->data_list, data);
                current->num_data++;
                current->is_leaf = 1;  
                free(diff_stem); 
                return;
            }

            diff_index += current->prefix_bit;
            diff_bit -= current->prefix_bit;
            free(diff_stem);
            diff_stem = createStem(key, diff_index, diff_bit);

            int bit = getBit(diff_stem, 0);
            if (bit == 0) {
                current = current->left;
            } else {
                current = current->right;
            }

        } else {
            // mismatching bit found at match_length
            int match_length = 0;
            for (int i = 0; i < current->prefix_bit && i < diff_bit; i++) {
                int bit1 = getBit(current->prefix, i);
                int bit2 = getBit(diff_stem, i);
                if (bit1 != bit2) {
                    match_length = i;
                    break;
                }
            }
            
            // store old node info
            char* old_prefix_buf = current->prefix;
            int old_prefix_bits = current->prefix_bit;
            list_t* old_data_list = current->data_list;
            int old_num_data = current->num_data;
            pnode_t* old_left = current->left;
            pnode_t* old_right = current->right;



            // update current node prefix to the matching part
            char* new_current_prefix = NULL;
            if (match_length > 0) {
                new_current_prefix = createStem(old_prefix_buf, 0, match_length);
            }
            current->prefix = new_current_prefix; // may be NULL if match_length==0
            current->prefix_bit = match_length;      
            current->is_leaf = 0;
            current->data_list = NULL;
            current->num_data = 0;
            current->left = NULL;
            current->right = NULL;

            // old child (old suffix)
            int old_suffix_bits = old_prefix_bits - match_length;
            char* old_suffix = createStem(old_prefix_buf, match_length, old_suffix_bits);
            pnode_t* old_child = make_pnode(old_suffix_bits, old_suffix);
            free(old_child->data_list);
            old_child->data_list = old_data_list;
            old_child->num_data = old_num_data;
            old_child->is_leaf = 1;
            old_child->left = old_left;
            old_child->right = old_right;

            // new child (new suffix)
            int new_suffix_bits = diff_bit - match_length;
            char* new_suffix = createStem(diff_stem, match_length, new_suffix_bits);
            pnode_t* new_child = make_pnode(new_suffix_bits, new_suffix);
            insert_at_foot(new_child->data_list, data);
            new_child->num_data = 1;
            new_child->is_leaf = 1;

            // attach by first bit after the split (0→left, 1→right)
            int old_bit = getBit(old_suffix, 0);
            if (old_bit == 0) {
                current->left = old_child;
                current->right = new_child;
            } else {
                current->right = old_child;
                current->left = new_child;
            }

            free(old_prefix_buf);
            free(diff_stem);
            return;

        }
        

    }

}

void find_closest(pnode_t* current, char* key, int* min_dist, pnode_t** min_node) {
    if (current != NULL) {
        if (current -> data_list != NULL) {
            char * node_key = current->data_list->head->data->EZI_ADD;
            int distance = editDistance(node_key, key, strlen(node_key), strlen(key));

            if (distance < *min_dist) {
                *min_dist = distance;
                *min_node = current;
            }
        }
        // traverse left
        find_closest(current->left, key, min_dist, min_node);
        // traverse right
        find_closest(current->right, key, min_dist, min_node);
    }

}

// helper to copy a data_list (shallow: copies node wrappers, not records)
static list_t* copy_list_shallow(list_t* src) {
    list_t* dst = make_empty_list();
    for (node_t* n = src ? src->head : NULL; n; n = n->next) {
        insert_at_foot(dst, n->data);   // copy pointer to record_t; do NOT free records twice
    }
    return dst;
}



void search_ptrie(ptrie_t* tree, char* key, result_t* result) {

    // not found
    if (tree == NULL || tree->root == NULL) {
        return;
    }

    int found;
    pnode_t *find_node = in_ptrie(tree, key, result, &found);
    if (found == 1 && find_node != NULL) {
        // exact match → copy its records into result list
        result->match = copy_list_shallow(find_node->data_list);
        result->num_matches = find_node->num_data;
        result->str_cmps++;                   // count a “string compare” at leaf
        return;
    }

    if (find_node != NULL) {
        // mismatch → pick closest descendant and copy its records
        int min_dist = INT_MAX;
        pnode_t* min_node = NULL;
        find_closest(find_node, key, &min_dist, &min_node);

        if (min_node != NULL) {
            result->match = copy_list_shallow(min_node->data_list);
            result->num_matches = min_node->num_data;
            result->str_cmps++;               // we did edit distance comparison(s)
        }
    }

}

void recursive_free_ptrie(pnode_t* current) {
    if (!current) return;

    recursive_free_ptrie(current->left);
    recursive_free_ptrie(current->right);

    free(current->prefix);
    if (current->data_list) {          // <-- guard to avoid free_list(NULL)
        free_list(current->data_list);
    }
    free(current);                      // <-- free the node itself
}


void free_ptrie(ptrie_t* tree) {
    if (tree != NULL) {
        recursive_free_ptrie(tree->root);
        free(tree);
    }

}


/* Returns min of 3 integers 
    reference: https://www.geeksforgeeks.org/edit-distance-in-c/ */
int min(int a, int b, int c) {
    if (a < b) {
        if(a < c) {
            return a;
        } else {
            return c;
        }
    } else {
        if(b < c) {
            return b;
        } else {
            return c;
        }
    }
}

/* Returns the edit distance of two strings
    reference: https://www.geeksforgeeks.org/edit-distance-in-c/ */
int editDistance(char *str1, char *str2, int n, int m){
    assert(m >= 0 && n >= 0 && (str1 || m == 0) && (str2 || n == 0));
    // Declare a 2D array to store the dynamic programming
    // table
    int dp[n + 1][m + 1];

    // Initialize the dp table
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            // If the first string is empty, the only option
            // is to insert all characters of the second
            // string
            if (i == 0) {
                dp[i][j] = j;
            }
            // If the second string is empty, the only
            // option is to remove all characters of the
            // first string
            else if (j == 0) {
                dp[i][j] = i;
            }
            // If the last characters are the same, no
            // modification is necessary to the string.
            else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = min(1 + dp[i - 1][j], 1 + dp[i][j - 1],
                    dp[i - 1][j - 1]);
            }
            // If the last characters are different,
            // consider all three operations and find the
            // minimum
            else {
                dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1],
                    dp[i - 1][j - 1]);
            }
        }
    }

    // Return the result from the dynamic programming table
    return dp[n][m];
}