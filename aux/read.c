#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Table structs
#include "create.c"


// If returns 1 valid, if returns 0 invalid.
// TODO: Should check for eof, for weird cases and prevent crashing.
int check_magic(uint8_t* a){
    if(a[0] == 0x53)
        if(a[1] == 0x41)
            if(a[2] == 0x54)
                if(a[3] == 0x55)
                    if(a[4] == 0x52)
                        if(a[5] == 0x4e)
                            return 1;
    return 0;
}


Table* read_table(char* path){
    FILE* f = fopen(path, "rb");
    if (f == NULL)
        exit(1) // Error
    

    Table* r_table = malloc(sizeof(Table));
    TABLE_HEADER* r_table_header = malloc(sizeof(TABLEHEADER));
    
    fread(r_table_header->magic, 1, 6, f); // Reads first 6 bytes.
    if (check_magic(r_table_header->magic) == 0) exit(1); // Magic number error

    fread(r_table_header->header_bytes, 1, 8, f); // Reads next 8 bytes as the number of bytes in the header
    fread(r_table_header->table_bytes, 1, 8, f); // Reads next 8 bytes

    fread(r_table_header->name, 1, TABLE_NAME_SIZE, f); // Reads the table name
    fread(r_table_header->attribute_number, 1, 1, f); // Reads number of attributes

    r_table_header->attribute_header = malloc((r_table_header->attribute_number)*sizeof(ATTRIBUTE_HEADER));
    fread(r_table_header->attribute_header, sizeof(ATTRIBUTE_HEADER), r_table_header->attribute_number, f); // Loads all the attribute headers

    r_table->table_header = r_table_header;

    int n_tuple = r_table_header->table_bytes - (27 + TABLE_NAME_SIZE + (r_table_header->attribute_number)*sizeof(ATTRIBUTE_HEADER));
    Tuple* r_data = malloc(n_tuple*sizeof(Tuple));

    // Add a byte identifier for the start of then data?
    fread(r_data, n_tuple, sizeof(Tuple), f);
    r_table->data = r_data;

    //f now should point to EOF
    fclose(f);
    return r_table;

}
