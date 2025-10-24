# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a C-based address dictionary search system that uses a Patricia Trie data structure for efficient string matching. The program reads address records from CSV files and performs fuzzy matching queries using edit distance calculations.

## Build and Run Commands

Build the project:
```bash
make
```

Clean build artifacts:
```bash
make clean
```

Run the program:
```bash
./dict2 <stage_number> <input_csv> <output_file> < <query_input>
```

Example execution:
```bash
./dict2 1 tests/dataset_1.csv output.out < tests/test1.in
```

## Architecture

### Core Data Structures

**Patricia Trie (`ptrie.h/c`)**: The main search data structure
- Implements a bit-wise Patricia Trie for efficient prefix matching
- Each node contains:
  - `prefix_bit`: number of bits in the prefix
  - `prefix`: the actual bit string
  - `left/right`: child pointers for binary branching
  - `data_list`: linked list of records at leaf nodes
  - `is_leaf`: flag indicating leaf status

**Dictionary (`dict.h/c`)**: Wrapper around Patricia Trie
- `dict_t` is a typedef for `ptrie_t`
- Handles CSV file parsing and trie construction
- Coordinates search operations and result formatting

**Record (`record.h/c`)**: Address record representation
- Contains 35 fields representing Australian address components (PFI, EZI_ADD, ROAD_NAME, POSTCODE, etc.)
- Each field is a dynamically allocated string (max 127 chars)
- Includes x,y coordinates as long doubles

**Result (`result.h/c`)**: Search result container
- Stores query key and matched records
- Tracks performance metrics: `bit_cmps`, `str_cmps`, `node_accesses`, `num_matches`
- Contains a linked list of matching records

**List (`list.h/c`)**: Generic linked list
- Simple singly-linked list with head/foot pointers
- Used to store multiple records at trie leaf nodes

**Bit utilities (`bit.h/c`)**: Bit-level operations
- `getBit()`: extracts individual bits from strings
- `createStem()`: creates bit substrings for trie navigation
- `cmp_bit()`: bit-wise string comparison with metrics tracking

### Program Flow

1. **Initialization**: Parse CSV file and build Patricia Trie (`create_dict()`)
2. **Query Processing**: Read queries from stdin line-by-line
3. **Search**: Navigate trie using bit-wise comparisons (`search_ptrie()`)
4. **Matching**: Use edit distance algorithm for fuzzy matching
5. **Output**: Print results to stdout and output file

### Key Implementation Details

- **Bit-wise navigation**: The trie uses bit-level comparisons (not character-level) for more granular prefix matching
- **Edit distance**: Uses dynamic programming algorithm for fuzzy string matching (implemented in `editDistance()`)
- **Dual output**: Results are printed to both stdout (summary statistics) and output file (full matching records)
- **Memory management**: All dynamic structures (trie nodes, records, lists) have corresponding free functions

## Testing

Test datasets are in `tests/` directory:
- `dataset_N.csv`: CSV files with N address records
- `testN.in`: Query inputs for corresponding datasets
- `testpartN.in`: Partial test queries

Expected outputs are in `matching_results/` directory:
- `testN.s2.out`: Expected file output for corresponding test input
- `testN.s2.stdout.out`: Expected stdout output for corresponding test input

Run tests by redirecting input from test files as shown in the run command above.

Example test validation:
```bash
./dict2 2 tests/dataset_1.csv output.out < tests/test1.in > output.stdout.out
diff output.out matching_results/test1.s2.out
diff output.stdout.out matching_results/test1.s2.stdout.out
```
