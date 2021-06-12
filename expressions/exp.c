

/*

CREATES A BUFFER

USES THE BUFFER TO GET AN INPUT FROM THE USER

PARSES THE INPUT AS AN EXPRESSION

THE PARSING SHOULD SEPARATE THE WORDS FOR THEN A TOKENIZATION




Possible expressions

SQL =>



login and db viewing

commands=

WILL START WITH A FORWARD SLASH

/u = user
/p = password
/db = select db

once the saturndb is initialized, there will be no db selected
the first action must be to login
if no login already exists, the user should be prompted a login creation line
once the user is logged, the db can be selected



*/



/*
#ifdef _WIN32
#include <windows.h>
#endif
*/

// FIX THE IMPORTED LIBRARY, A LOT OF SHIT NOT USED
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

#define BUFFER_SIZE = 256


// Structure of a simple Buffer
typedef struct Buffer{
    char stream[BUFFER_SIZE];
    uint8_t size;
} Buffer;

typedef struct Parsed_buffer{
    char** words;
    uint8_t counter;
}Parsed_buffer;
// ...
Buffer* create_buffer(void){
    Buffer* buffer = malloc(sizeof(Buffer));
    for(int i = 0; i < BUFFER_SIZE; i++) buffer->stream[i] = '\0';
    return buffer;
}

//
void get_input(Buffer* b){
    int counter = 0;
    char c;
    while(scanf("%c", &c) != '\n' && counter < BUFFER_SIZE){
        b->stream[counter] = c;
        counter++;
    }
    b->size = counter;
    // Treat the 100k possible errors from this input

// Returns the array of words from the buffer
Parsed_buffer* parse_input(Buffer* b){
    int v[b->size * 2] = 0;
    int v_ind = 0;
    int i = 0;
    int mode = 1;
    int word_counter = 0;
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
            word_counter++;
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
    Parsed_buffer* return_struct = malloc(sizeof(Parsed_buffer));
    return_struct->words = args;
    return_struct->counter = word_counter;
    return return_struct;
}

Token_array* tokenize_input(Parsed_buffer* b){
    /*
    Token possibilites:
        
    */
}