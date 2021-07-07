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

#define TABLE_NAME_SIZE 255
#define ATTRIBUTE_NAME_SIZE 255
#define ATTRIBUTE_DATATYPE_SIZE 255

typedef struct TABLE_HEADER{
    uint8_t magic[6]; // file magic numbers, translate to SATURN in ascii
    uint64_t header_bytes; // how many bytes until data begins
    uint64_t table_bytes; // how many bytes until whole table data ends == file size
    char name[TABLE_NAME_SIZE]; // Table name
    uint64_t tuples;
    uint64_t tuple_size; // size of the tuple in bytes
    uint8_t attribute_number; // how many attributes are in the table, max 255 for now
    ATTRIBUTE_HEADER* attribute_header;
} TABLE_HEADER;

typedef struct ATTRIBUTE_HEADER{
    char name[ATTRIBUTE_NAME_SIZE];
    char data_type[ATTRIBUTE_DATATYPE_SIZE];
    uint8_t data_bytes;
} ATTRIBUTE_HEADER;


typedef struct TABLE{
    TABLE_HEADER* table_header;
    TUPLE* data;
} TABLE;

typedef struct Tuple{
    uint8_t* byte;    
} Tuple;

typedef struct Table_creation{
    char name[TABLE_NAME_SIZE];
    Attribute* 
} Table_creation;
/*
typedef struct DATA_HEADER{

} DATA_HEADER;
*/

//remove table_creation struct and work from SQL_EXPRESSION to Table
Table* create_table(Table_creation* tb){

    // New table.
    Table* table = malloc(sizeof(Table));

    // New Table's header.
    TABLE_HEADER* table_header = malloc(sizeof(TABLE_HEADER));

    // Name of the table.
    table_header->name = <name>;

    // Array of Attribute headers 
    ATTRIBUTE_HEADER** attr_header = malloc(<n_of_attributes> * sizeof(ATTRIBUTE_HEADER*));

    // Updates the attribute metadata.
    table->attribute_header = attr_header;
    table->attribute_number = <tb_attr_n>;

    // Fills the attribute headers
    for(int i =0; i < <n_of_attributes>; i++){
        attr_header[i]->name = <tb_attri_i_name>;
        attr_header[i]->data_type = <tb_attri_i_type>;
        attr_header[i]->data_bytes = <tb_attri_i_bytes>;
    } 

    // Calculates the header size
    // Table will be the same as the header, because there is no data yet.
    table->header_bytes = 398 + <n_of_attributes> * sizeof(ATTRIBUTE_HEADER);
    table->table_bytes = table->header_bytes;

    return table;

    /*
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

    */
    

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

