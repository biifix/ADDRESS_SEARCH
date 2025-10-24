#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "record.h"

/* Parse one CSV line into a record_t */
record_t *create_record(char *line) {
    record_t *record = malloc(sizeof(record_t));
    assert(record != NULL);

    char* fields[NUM_FIELDS];
    char field_temp[MAX_FIELD_LEN + 1];

    int i = 0;  // Index for the line
    int in_quote = 0; // Flag to track if we are inside a quoted field
    int field_index = 0; // Index for the fields
    int field_len = 0; // Length of the current field


    while (line[i] != '\0' && line[i] != EOF && (in_quote || line[i] != '\n')) {
        if (line[i] == ',' && in_quote == 0) {

            // End of a field, store it
            field_temp[field_len] = '\0';
            fields[field_index] = strdup(field_temp);
            field_index++;
            field_len = 0;
            
            // encounters boundary, toggle in_quote status
        } else if (line[i] == '"') {
            in_quote = 1 - in_quote;
       
        } else {
            if (field_len < MAX_FIELD_LEN) {
                field_temp[field_len++] = line[i];
            }
        }
        i++;
    }

    // Handle the last field
    field_temp[field_len] = '\0';
    fields[field_index] = strdup(field_temp);
    field_index++;
    
    // Fill missing fields with empty strings
    while (field_index < NUM_FIELDS) {
        fields[field_index++] = strdup("");
    }

    // Assign fields to the record
    record->PFI = fields[0];
    record->EZI_ADD = fields[1];
    record->SRC_VERIF = fields[2];
    record->PROPSTATUS = fields[3];
    record->GCODEFEAT = fields[4];
    record->LOC_DESC = fields[5];
    record->BLGUNTTYP = fields[6];
    record->HSAUNITID = fields[7];
    record->BUNIT_PRE1 = fields[8];
    record->BUNIT_ID1 = fields[9];
    record->BUNIT_SUF1 = fields[10];
    record->BUNIT_PRE2 = fields[11];
    record->BUNIT_ID2 = fields[12];
    record->BUNIT_SUF2 = fields[13];
    record->FLOOR_TYPE = fields[14];
    record->FLOOR_NO_1 = fields[15];
    record->FLOOR_NO_2 = fields[16];
    record->BUILDING = fields[17];
    record->COMPLEX = fields[18];
    record->HSE_PREF1 = fields[19];
    record->HSE_NUM1 = fields[20];
    record->HSE_SUF1 = fields[21];
    record->HSE_PREF2 = fields[22];
    record->HSE_NUM2 = fields[23];
    record->HSE_SUF2 = fields[24];
    record->DISP_NUM1 = fields[25];
    record->ROAD_NAME = fields[26];
    record->ROAD_TYPE = fields[27];
    record->RD_SUF = fields[28];
    record->LOCALITY = fields[29];
    record->STATE = fields[30];
    record->POSTCODE = fields[31];
    record->ACCESSTYPE = fields[32];

    record->x = strtold(fields[33], NULL);
    free(fields[33]); // Free the string after conversion
    record->y = strtold(fields[34], NULL);
    free(fields[34]); // Free the string after conversion

    return record;


}


/*print one record to output file*/
void print_record(record_t *record, FILE *out) {
    fprintf(out,
        "--> PFI: %s || EZI_ADD: %s || SRC_VERIF: %s || PROPSTATUS: %s || GCODEFEAT: %s || LOC_DESC: %s || "
        "BLGUNTTYP: %s || HSAUNITID: %s || BUNIT_PRE1: %s || BUNIT_ID1: %s || BUNIT_SUF1: %s || "
        "BUNIT_PRE2: %s || BUNIT_ID2: %s || BUNIT_SUF2: %s || FLOOR_TYPE: %s || FLOOR_NO_1: %s || "
        "FLOOR_NO_2: %s || BUILDING: %s || COMPLEX: %s || HSE_PREF1: %s || HSE_NUM1: %s || "
        "HSE_SUF1: %s || HSE_PREF2: %s || HSE_NUM2: %s || HSE_SUF2: %s || DISP_NUM1: %s || "
        "ROAD_NAME: %s || ROAD_TYPE: %s || RD_SUF: %s || LOCALITY: %s || STATE: %s || "
        "POSTCODE: %s || ACCESSTYPE: %s || x: %.5Lf || y: %.5Lf || \n",
        record->PFI, record->EZI_ADD, record->SRC_VERIF, record->PROPSTATUS, record->GCODEFEAT, record->LOC_DESC,
        record->BLGUNTTYP, record->HSAUNITID, record->BUNIT_PRE1, record->BUNIT_ID1, record->BUNIT_SUF1,
        record->BUNIT_PRE2, record->BUNIT_ID2, record->BUNIT_SUF2, record->FLOOR_TYPE, record->FLOOR_NO_1,
        record->FLOOR_NO_2, record->BUILDING, record->COMPLEX, record->HSE_PREF1, record->HSE_NUM1,
        record->HSE_SUF1, record->HSE_PREF2, record->HSE_NUM2, record->HSE_SUF2, record->DISP_NUM1,
        record->ROAD_NAME, record->ROAD_TYPE, record->RD_SUF, record->LOCALITY, record->STATE,
        record->POSTCODE, record->ACCESSTYPE, record->x, record->y
    );
}

/* free memory of a record */
void free_record(record_t *record) {
    if (record != NULL) {

        free(record->PFI);
        free(record->EZI_ADD);
        free(record->SRC_VERIF);
        free(record->PROPSTATUS);
        free(record->GCODEFEAT);
        free(record->LOC_DESC);
        free(record->BLGUNTTYP);
        free(record->HSAUNITID);
        free(record->BUNIT_PRE1);
        free(record->BUNIT_ID1);
        free(record->BUNIT_SUF1);
        free(record->BUNIT_PRE2);
        free(record->BUNIT_ID2);
        free(record->BUNIT_SUF2);
        free(record->FLOOR_TYPE);
        free(record->FLOOR_NO_1);
        free(record->FLOOR_NO_2);
        free(record->BUILDING);
        free(record->COMPLEX);
        free(record->HSE_PREF1);
        free(record->HSE_NUM1);
        free(record->HSE_SUF1);
        free(record->HSE_PREF2);
        free(record->HSE_NUM2);
        free(record->HSE_SUF2);
        free(record->DISP_NUM1);
        free(record->ROAD_NAME);
        free(record->ROAD_TYPE);
        free(record->RD_SUF);
        free(record->LOCALITY);
        free(record->STATE);
        free(record->POSTCODE);
        free(record->ACCESSTYPE);

        // Free the record structure itself
        free(record);
    }
}
