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

typedef struct Table{

} TABLE;

typedef struct Attribute{
    
} Attribute;

typedef struct Tuple{
    
} Tuple;

typedef struct Buffer{
    char stream[BUFFER_SIZE];

} Buffer;

Buffer create_buffer(void){
    Buffer buffer;
    for(int i = 0; i < BUFFER_SIZE; i++) buffer.stream[i] = '\0';
    return buffer;
}

void get_input(Buffer b){
    int counter = 0;
    char c;
    while(scanf("%c", &c) != '\n' && counter < BUFFER_SIZE){
        b.stream[counter] = c;
    }
    // Treat the 100k possible errors from this input


void parse_input(Buffer b){
    input = b.stream;
    int v[BUFFER_SIZE] = 0; // the number of words will never be as big as the buffer size
    int word_count = 0;

    for(int i = 0; i < BUFFER_SIZE; i++){// Treat the cases with more than one space in between the words
        if (input[i] == ' ' || input[i] == '\0'){
            v[word_count] == i;
            word_count++;
            if (input[i] == '\0') break;
        }

    } 

    char** args = malloc(word_count * sizeof(char*));
    for(int i = 0; i < word_count; i++){
        if (i == 0){
            args[i] = malloc((v[1] - 1) * sizeof(char));
            char* word[v[1]];
 
            for(int k = 0; k < v[1] - 1; k++) word[k] = input[k];
            word[v[1]-1] = NULL;
            //strcpy(args[i], )
        }
        args[i] = malloc((v[i] - v[i-1] - 1) * sizeof(char)) // There is no -1 anymore for the '\0' space
    }
}

uint8_t create_table(void){
    
}

uint8_t create_attribute(){

}

uint8_t create_tuple(){

}



int main(int argc, char* argv[]){

}