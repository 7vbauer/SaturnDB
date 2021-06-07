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

    return args;
}



Table* create_table(void){


    
}

Attribute* create_attribute(){

}

Tuple* create_tuple(){

}



int main(int argc, char* argv[]){

}
