#ifndef RECORD_H
#define RECORD_H

#define NUM_FIELDS 35
#define MAX_FIELD_LEN 127
#include <stdio.h>

typedef struct {
    char *PFI;
    char *EZI_ADD;
    char *SRC_VERIF;
    char *PROPSTATUS;
    char *GCODEFEAT;
    char *LOC_DESC;
    char *BLGUNTTYP;
    char *HSAUNITID;
    char *BUNIT_PRE1;
    char *BUNIT_ID1;
    char *BUNIT_SUF1;
    char *BUNIT_PRE2;
    char *BUNIT_ID2;
    char *BUNIT_SUF2;
    char *FLOOR_TYPE;
    char *FLOOR_NO_1;
    char *FLOOR_NO_2;
    char *BUILDING;
    char *COMPLEX;
    char *HSE_PREF1;
    char *HSE_NUM1;
    char *HSE_SUF1;
    char *HSE_PREF2;
    char *HSE_NUM2;
    char *HSE_SUF2;
    char *DISP_NUM1;
    char *ROAD_NAME;
    char *ROAD_TYPE;
    char *RD_SUF;
    char *LOCALITY;
    char *STATE;
    char *POSTCODE;
    char *ACCESSTYPE;
    long double x;
    long double y;
} record_t;

record_t *create_record(char *line);
void print_record(record_t *record, FILE* out);
void free_record(record_t *record);

#endif
