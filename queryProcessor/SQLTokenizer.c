
#include <stdint.h>
#include <ctype.h>



#define SQL_PARSER_LENGTH 256
#define BUFFER_LENGTH 256

// I prefer the typedef struct struct_name {...} struct_name;
// but it seems that some compilers don't like it much. Sadge.

struct Sql_Expression{
    unsigned int * tokens;
    unsigned int n_tokens;
    char** strings;
    unsigned int n_strings;
    unsigned int* pos_strings;
}
typedef struct Sql_Expression Sql_Expression;

struct Sql_Parser{
    unsigned int tokens[SQL_PARSER_LENGTH];
    char** strings;
    unsigned int n_strings;
    unsigned int exp_type;
    unsigned int* pos_strings;
}
typedef struct Sql_Parser Sql_Parser;

struct Query{
    char* table;
    char** columns;
    int n_columns;
    //QUALIFIER* qualifier;
};
typedef struct Query Query;

//--------------------------------

typedef enum {
    STATE_INIT,
    STATE_SELECT,
    STATE_FROM,
    STATE_COMMA, 
    //STATE_SEMICOLON,
    //STATE_ASTERISC,
    STATE_STRING,
    //STATE_INVALID_CHAR
} State;

typedef enum {
    SQL_TOKEN_SELECT, 
    SQL_TOKEN_COMMA, 
    SQL_TOKEN_FROM, 
    SQL_TOKEN_SEMICOLON, 
    SQL_TOKEN_STRING,
    SQL_TOKEN_ASTERISC
} Token;

int check_char(char c){
    if (isalpha(c) || c == '"' || c == '\'') 
        return 1;
    return 0;
}

Sql_Expression* parser(const char* text){
    enum State state = STATE_INIT;
    char event;
    int index = 0;
    int token_index = 0;
    char buffer[BUFFER_LENGTH];
    while(1){
        switch(state){
            case(STATE_INIT):
                switch(tolower(text[index])){
                    case('s'):
                        state = STATE_SELECT;
                        buffer[token_index++] = text[index];
                        break;
                    case('f'):
                        state = STATE_FROM;
                        buffer[token_index++] = text[index];
                        break;
                    case('*'):
                        state = STATE_ASTERISC;
                        buffer[token_index++] = text[index];
                        break;
                    case(','):
                        state = STATE_COMMA;
                        buffer[token_index++] = text[index];
                        break;
                    default:  //Strings
                        if (check_char(tolower(text[index])))
                            state = STATE_STRING;
                        else
                            state = STATE_INVALID_CHAR;
                        token_index++;
                }
                break;
            case(STATE_SELECT):
                switch(tolower(text[index])){
                    case():
                    case():
                }
                break;
            case(STATE_ASTERISC):
            case(STATE_FROM):
            case(STATE_COMMA):
            case(STATE_SEMICOLON):
        }
        index++;
    }

}