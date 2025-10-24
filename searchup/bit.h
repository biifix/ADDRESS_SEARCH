/* Number of bits in a single character. */
#define BITS_PER_BYTE 8

char *createStem(char *oldKey, unsigned int startBit, unsigned int numBits);

int getBit(char *s, unsigned int bitIndex);
int cmp_bit(char *key1, char *key2, int *bit_cmps, int *str_cmps);
