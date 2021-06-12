
#ifdef linux
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#endif

#include <stdint.h>
#include <stdio.h>
#include <sql.h>
#include <sqlext.h>



typedef struct TABLE_HEADER{
    uint64_t header_bytes; // how many bytes until data begins
    uint64_t table_bytes; // how many bytes until whole table data ends == file size
    char name[256];
    uint8_t attribute_number; // how many attributes are in the table, max 255 for now
    ATTRIBUTE_HEADER* attribute_header;
} TABLE_HEADER;

typedef struct ATTRIBUTE_HEADER{
    char name[256];
    char data_type[256];
    uint64_t data_bytes;
} ATTRIBUTE_HEADER;

typedef struct DATA{
    char x;
} DATA;

typedef struct Table{
    TABLE_HEADER* table_header;
    DATA* data;
} TABLE;

typedef struct Attribute{
    
} Attribute;

typedef struct Tuple{
    
} Tuple;

typedef struct Table_creation{
    char name[256];
    Attribute* 
} Table_creation;
/*
typedef struct DATA_HEADER{

} DATA_HEADER;
*/

Table* create_table(Table_creation* tb){

    TABLE_HEADER* new_table_header = malloc(sizeof(TABLE_HEADER));
    new_table_header->name = tb->table_name;

    ATTRIBUTE_HEADER* new_attribute_header = malloc(new_table_header->attribute_number * sizeof(ATTRIBUTE_HEADER));

    if (new_attribute_header == NULL){
        // TODO: Treat the errors with the error library !!!!!
        return NULL;
    }

    new_table_header->attribute_number = tb->attribute_number;
    new_table_header->attribute_header = new_attribute_header;
    
    for(int i = 0; i < new_table_header->attribute_number; i++){
        new_table_header->attribute_header[i] = malloc(sizeof(ATTRIBUTE_HEADER));
        if (new_table_header->attribute_header[i] == NULL){
            return NULL;
            //Error
        }
        (new_table_header->attribute_header[i])->name = (tb->attr[i])->name;
        (new_table_header->attribute_header[i])->data_type = (tb->attr[i])->data_type;
        (new_table_header->attribute_header[i])->data_bytes = (tb->attr[i])->data_bytes;
    }

    Table* new_table = malloc(sizeof(Table));


    return &new_table;

    

}

Tuple* create_tuple(ATTRIBUTE_HEADER* attributes, uint8_t quantity){
    uint64_t total_bytes = 0;
    for(int i = 0; i < quantity; i++) total_bytes += attributes[i]->data_bytes;
    uint8_t* block = malloc(total_bytes);


}

uint8_t insert_tuple(uint8_t* data){
    
    return 1;
    
    return 0;



}

