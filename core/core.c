/*



select
create
insert
update
delete
drop



databases
tables
attributes
tuples



databases = database <x>, database back, drop <x>

table = table <x>, drop <x>



pwd = \db\table


"SELECT", "CREATE", "UPDATE", "DELETE", "DROP", "ALTER", "TABLE", "INDEX"

""


select table
insert 
create table/db
update table
delete data
drop table/db

https://www.easysoft.com/developer/languages/c/odbc_tutorial.html

technically SGBD use ODBC


DATA:

INT
LONG
DOUBLE
CHAR <X>








*/


#include <stdint.h>
#include <stdio.h>
#include <sql.h>
#include <sqlext.h>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef linux
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#endif

#define BUFFER_SIZE = 256



typedef struct Buffer{
    char stream[BUFFER_SIZE];

} Buffer;


Buffer* create_buffer(void){
    Buffer* buffer = malloc(sizeof(Buffer));
    for(int i = 0; i < BUFFER_SIZE; i++) buffer->stream[i] = '\0';
    return buffer;
}

void get_input(Buffer* b){
    int counter = 0;
    char c;
    while(scanf("%c", &c) != '\n' && counter < BUFFER_SIZE){
        b->stream[counter] = c;
        counter++;
    }
    b->size = counter;
    // Treat the 100k possible errors from this input


char** parse_input(Buffer* b){
    int v[b->size * 2] = 0;
    int v_ind = 0;
    int i = 0;
    int mode = 0;
    while(1){
        /*
        mode 0 == recebendo nome
        mode 1 == espaço em branco
        */
        // '\n' after backspaces
        if (b->stream[i] == '\n' && mode == 1) break;
        // '\n' after text
        else if (b->stream[i] == '\n' && mode == 0){
            v[v_ind] == i - 1;
            i++;
            break;
        }
        // backspace after backspace
        else if (b->stream[i] == ' ' && mode == 1) i++;
        // backspace after text
        else if (b->stream[i] == ' ' && mode == 0){
            v[v_ind++] == i - 1;
            mode = 1;
            i++;
        }  
        // text after backspace
        else if (b->stream[i] != ' ' && mode == 1){
            v[v_ind++] = i;
            mode = 0;
            i++;
        }
        // text after text
        else if (b->stream[i] != ' ' && mode == 0)i++;
        else{
            i++;
            // TODO: Treat the unexpected state with the error library
        }
    }

    // Try to rewrite this whole thing with strcpy()
    // Issue is, the args in the b->stream do not end with a '\0'.
    char** args = malloc(b->size * sizeof(char*));
    for (int j = 0; j < size; j++){
        arg_size = v[j*2+1] - v[j*2] + 1 + 1; // An additional +1 for the '\0' char. Explicit on purpose.
        args[j] = malloc(arg_size * sizeof(char));
        int tmp_c = v[j*2];
        while(tmp_c <= v[j*2]+1){
            args[j][tmp_c - v[j*2]] = b->stream[tmp_c];
            tmp_c++;
        }
        args[j][tmp_c] == '\0';
    }

    // At this stage, args should carry the words followed by '\0'

    return &args;
}

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



int main(int argc, char* argv[]){

}
