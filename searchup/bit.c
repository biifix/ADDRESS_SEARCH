#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "bit.h"

int getBit(char *s, unsigned int bitIndex){
    assert(s && bitIndex >= 0);
    unsigned int byte = bitIndex / BITS_PER_BYTE;
    unsigned int indexFromLeft = bitIndex % BITS_PER_BYTE;
    /* 
        Since we split from the highest order bit first, the bit we are interested
        will be the highest order bit, rather than a bit that occurs at the end of the
        number. 
    */
    unsigned int offset = (BITS_PER_BYTE - (indexFromLeft) - 1) % BITS_PER_BYTE;
    unsigned char byteOfInterest = s[byte];
    unsigned int offsetMask = (1 << offset);
    unsigned int maskedByte = (byteOfInterest & offsetMask);
    /*
        The masked byte will still have the bit in its original position, to return
        either 0 or 1, we need to move the bit to the lowest order bit in the number.
    */
    unsigned int bitOnly = maskedByte >> offset;
    return bitOnly;
}

/* 
 bitwise string compare with counting
    - returns 0 if the strings are equal
    - returns 1 if first differing bit in key1 is 1 and in key2 is 0
    - returns -1 if first differing bit in key1 is 0 and in key2
    - record # of bit compared and string compared
*/
int cmp_bit(char *key1, char *key2, int *bit_cmps, int *str_cmps) {
    assert(key1 != NULL && key2 != NULL);
    assert(bit_cmps != NULL && str_cmps != NULL);

    (*str_cmps)++;

    // include NULL bytes in the comparison
    int len1 = strlen(key1) + 1;
    int len2 = strlen(key2) + 1;
    int num_bits;

    if (len1 < len2) {
        num_bits = len1 * BITS_PER_BYTE;
    } else {
        num_bits = len2 * BITS_PER_BYTE;
    }   

    int i = 0;
    
    // Compare bits one by one of key1 and key2 and look for differing bits
    for (i = 0; i < num_bits; i++) {
        (*bit_cmps)++;

        int bit1 = getBit(key1, (unsigned int)i);
        int bit2 = getBit(key2, (unsigned int)i);

        if (bit1 > bit2) {
            return 1;
        } else if (bit1 < bit2) {
            return -1;
        }
    }
    // If all bits are equal, return 0
    return 0;
}


/* Allocates new memory to hold the numBits specified and fills the allocated
    memory with the numBits specified starting from the startBit of the oldKey
    array of bytes. */

char *createStem(char *oldKey, unsigned int startBit, unsigned int numBits){
    assert(numBits > 0 && startBit >= 0 && oldKey);
    int extraBytes = 0;
    if((numBits % BITS_PER_BYTE) > 0){
        extraBytes = 1;
    }
    int totalBytes = (numBits / BITS_PER_BYTE) + extraBytes;
    char *newStem = malloc(sizeof(char) * totalBytes);
    assert(newStem);
    for(unsigned int i = 0; i < totalBytes; i++){
        newStem[i] = 0;
    }
    for(unsigned int i = 0; i < numBits; i++){
        unsigned int indexFromLeft = i % BITS_PER_BYTE;
        unsigned int offset = (BITS_PER_BYTE - indexFromLeft - 1) % BITS_PER_BYTE;
        unsigned int bitMaskForPosition = 1 << offset;
        unsigned int bitValueAtPosition = getBit(oldKey, startBit + i);
        unsigned int byteInNewStem = i / BITS_PER_BYTE;
        newStem[byteInNewStem] |= bitMaskForPosition * bitValueAtPosition;
    }
    return newStem;
}
