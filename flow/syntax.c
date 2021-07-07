#ifdef linux
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#endif
/*

#include <stdint.h>
#include <stdio.h>
#include <sql.h>
#include <sqlext.h>

*/
#define SQL_EXPRESSION_AUX_LENGTH 256

#define SELECT_TOKEN 4
#define CREATE_TOKEN 5
#define INSERT_TOKEN 6
#define INTO_TOKEN 7
#define UPDATE_TOKEN 8
#define DELETE_TOKEN 9
#define DROP_TOKEN 10
#define OPEN_PARENTESIS_TOKEN 12
#define CLOSE_PARENTESIS_TOKEN 13
#define COMMA_TOKEN 0
#define SEMICOLON_TOKEN 1
#define DOUBLE_QUOTE_TOKEN 2
#define SINGLE_QUOTE_TOKEN 11
#define STRING_TOKEN 3
#define ASTERISC_TOKEN 14
#define FROM_TOKEN 15
#define NULL_TOKEN 255
#define DATABASE_TOKEN 16
#define TABLE_TOKEN 17

// Use a temporary struct 'pair' to store the strings positions
// EXPRESSIONS MUST HAVE TOKENS SEPÁRATED BY BACKSPACE, ISSUES WITH SPECIAL ASTERIC


typedef struct SQL_EXPRESSION{
    unsigned int * tokens;
    unsigned int n_tokens;
    char** strings;
    unsigned int n_strings;
    unsigned int* pos_strings;

}SQL_EXPRESSION;


typedef struct SQL_EXPRESSION_AUX{
    unsigned int tokens[SQL_EXPRESSION_AUX_LENGTH];
    char** strings;
    unsigned int n_strings;
    unsigned int exp_type;
    unsigned int* pos_strings;

}SQL_EXPRESSION_AUX;


typedef struct QUERY{
    char* table;
    char** columns;
    int n_columns;
    //QUALIFIER* qualifier;
}QUERY;

typedef struct QUALIFIER{
    int a;
}QUALIFIER;
/*
              4       5         6           7       8     9          
reserved = SELECT, CREATE, INSERT INTO, UPDATE, DELETE, DROP
symbols = OPEN_PARENTESIS, CLOSE_PARENTESIS, COMMA, SEMICOLON, DOUBLE_QUOTE
string                                         0        1           2
   3




type => 0 select, 1, insert, 2, 3 update, 4 create, 5 delete, 6 drop 
*/

/*
TABLE* resolve_creation(CREATION* creation){

}

TABLE* resolve_query(QUERY* query){
    // Get pointer to table
    // Cut only asked attributes
    // Go through the qualifiers
    // Go through the orderby
}

int specify_expression(SQL_EXPRESSION* sql){
    // checks if the expression is valid and calls
    // for the apropriate method
}
*/

// Function with the purpose of cutting off the excess of memory usage from inital buffers.
SQL_EXPRESSION* prettifier(SQL_EXPRESSION_AUX* s){
    SQL_EXPRESSION* sql_r = malloc(sizeof(SQL_EXPRESSION));

    for(int i = 0; i < SQL_EXPRESSION_AUX_LENGTH; i++){
        if (s->tokens[i] != NULL_TOKEN)
            sql_r->n_tokens++;
        else
            break;
    }

    sql_r->tokens = malloc((sql_r->n_tokens) * sizeof(unsigned int));

    for(int i = 0; i < sql_r->n_tokens; i++)
        sql_r->tokens[i] = s->tokens[i];

    sql_r->strings = malloc(s->n_strings * sizeof(char*));
    sql_r->n_strings = s->n_strings;

    for(int i = 0; i < sql_r->n_strings; i++)
        sql_r->strings[i] = s->strings[i];

    sql_r->pos_strings = malloc(sql_r->n_strings * sizeof(unsigned int));
    for(int i = 0; i < sql_r->n_strings; i++)
        sql_r->pos_strings[i] = s->pos_strings[i];

    free(s->strings);
    free(s->pos_strings);
    free(s);

    return sql_r;
    
}

char* capture_string(char* text, unsigned int * index, const char* start){

    int size = strlen(start);
    int new = 0;
    char* bff = malloc(256*sizeof(char));
    /*
        Index now contains the last char that escaped the "keyword chain".
        So current char postiion should be treated.

        if p is a char pointer:
            return p;
                ==
            return &(p[0]);
    */

    while(isalpha(text[*index]) != 0 || isdigit(text[*index]) != 0 || text[*index] == '_'){
        bff[new] = text[*index];
        //strncpy(&bff[new], &text[*index], 1);
        (*index)++;
        /*
            In the case of the last iteration, the index variable
            will be "pointing" to a char that isn't part of the string
            BUT still must be checked by the parse() function.
        */
        new++;
    }
    /*
    do{
        y++;
        strncpy(&bff[new], &text[*index], 1);
        (*index)++;

            In the case of the last iteration, the index variable
            will be "pointing" to a char that isn't part of the string
            BUT still must be checked by the parse() function.

        new++;
    }while(isalpha(text[*index]) == 0 && isdigit(text[*index]) == 0);
    */
    bff[++new] = '\0';
    //strncpy(&bff[++new], '\0', 1); cant pass a null char

    /*
        At this point:
            start => a string that should be the preffix of the returned string.
            bff => a string that should be the suffix of the returned string, plus a NULL char.
            r_string => a pointer with enough space for start and bff contents.
    */
    char* r_string = malloc((size+new)*sizeof(char));
    strcpy(r_string, start);
    strcpy(&(r_string[size]), bff);
    free(bff);
    // NEED TO TEST EVERY PIECE OF CODE HERE.
    // NOT SURE ABOUT THE NULL CHAR BEHAVIOR IN SOME OF THESE FUNCTIONS.....    
    return r_string;

}

SQL_EXPRESSION_AUX* parse(char* input){
    // So far we'll only accept lower cap letters.

    //printf("%zu\n",  strlen(input));
    for(int i = 0; i < strlen(input); i++)
        input[i] = tolower(input[i]);
    
    // Input must end with a NULL char.
    // index is the position in the input text.
    unsigned int index = 0;
    // c_token keeps the token count/index.
    unsigned int c_token = 0;

    char** tmp_string_pointers = malloc(SQL_EXPRESSION_AUX_LENGTH * sizeof(char*));
    for(int i = 0; i < 256; i++)
        tmp_string_pointers[i] = NULL;

    unsigned int tmp_string_index = 0;

    SQL_EXPRESSION_AUX* sql = malloc(sizeof(SQL_EXPRESSION_AUX));
    sql->strings = tmp_string_pointers;
    sql->n_strings = 0;

    for(int i = 0; i < SQL_EXPRESSION_AUX_LENGTH; i++)
        sql->tokens[i] = NULL_TOKEN;

    sql->pos_strings = malloc(SQL_EXPRESSION_AUX_LENGTH * sizeof(unsigned int));
    for(int i = 0; i < SQL_EXPRESSION_AUX_LENGTH; i++)
        sql->pos_strings[i] = NULL_TOKEN;

    // Loops until the input string ends. 
    while(index < strlen(input)){
        // Char is a space, so not a token.
        if (input[index] == ' ') index++;
        // Char is a comma, capture token. Does not need a backspace char after.
        else if (input[index] == ','){
            sql->tokens[c_token++] = COMMA_TOKEN;
            index++;
        } 
        else if (input[index] == '('){
            sql->tokens[c_token++] = OPEN_PARENTESIS_TOKEN;
            index++;
        }
        else if (input[index] == ')'){
            sql->tokens[c_token++] = CLOSE_PARENTESIS_TOKEN;
            index++;
        }
        else if (input[index] == '*'){
            sql->tokens[c_token++] = ASTERISC_TOKEN;
            index++;
        }
        // Final char in the expression. Capture and then break loop.
        else if (input[index] == ';'){
            sql->tokens[c_token++] = SEMICOLON_TOKEN;
            break;
        }
        // Not sure if necessary, but gets the whole string in between the double quotes.
        //if (input[index] == '"');
        else if (input[index] == 's'){
            index++;
            if (input[index] == 'e'){
                index++;
                if (input[index] == 'l'){
                    index++;
                    if (input[index] == 'e'){
                        index++;
                        if (input[index] == 'c'){
                            index++;
                            if (input[index] == 't'){
                                index++;
                                if (input[index] == ' '){
                                    sql->tokens[c_token++]= SELECT_TOKEN;
                                    
                                    index++;
                                }else{
                                    // Get string after SELECT...
                                    tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "select");
                                    sql->tokens[c_token++] = STRING_TOKEN;
                                    sql->pos_strings[sql->n_strings++] = c_token-1;
                                }
                            }else{
                                // Get string after SELECT...
                                tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "selec");
                                sql->tokens[c_token++] = STRING_TOKEN;
                                sql->pos_strings[sql->n_strings++] = c_token-1;
                            }
                        }else{  
                            // Get string after SELEC...
                            tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "sele");
                            sql->tokens[c_token++] = STRING_TOKEN;
                            sql->pos_strings[sql->n_strings++] = c_token-1;
                        }       
                    }else{
                        // Get string after SELE...
                        tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "sel");
                        sql->tokens[c_token++] = STRING_TOKEN;
                        sql->pos_strings[sql->n_strings++] = c_token-1;
                    }
                }else{
                    // Get string after SEL...
                    tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "se");
                    sql->tokens[c_token++] = STRING_TOKEN;
                    sql->pos_strings[sql->n_strings++] = c_token-1;
                }
            }else{
                // Get string after SE...
                tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "s");
                sql->tokens[c_token++] = STRING_TOKEN;
                sql->pos_strings[sql->n_strings++] = c_token-1;
            }
        }
        else if (input[index] == 'c'){
            index++;
            if (input[index] == 'r'){
                index++;
                if (input[index] == 'e'){
                    index++;
                    if (input[index] == 'a'){
                        index++;
                        if (input[index] == 't'){
                            index++;
                            if (input[index] == 'e'){
                                index++;
                                if (input[index] == ' '){
                                    sql->tokens[c_token++] = CREATE_TOKEN;
                                    index++;
                                }else{
                                    tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "create");
                                    sql->tokens[c_token++] = STRING_TOKEN;
                                    sql->pos_strings[sql->n_strings++] = c_token-1;
                                }
                            }else{
                                tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "creat");
                                sql->tokens[c_token++] = STRING_TOKEN;
                                sql->pos_strings[sql->n_strings++] = c_token-1;
                            }
                        }else{
                            tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "crea");
                            sql->tokens[c_token++] = STRING_TOKEN;
                            sql->pos_strings[sql->n_strings++] = c_token-1;
                        }
                    }else{
                        tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "cre");
                        sql->tokens[c_token++] = STRING_TOKEN;
                        sql->pos_strings[sql->n_strings++] = c_token-1;
                    }
                }else{
                    tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "cr");
                    sql->tokens[c_token++] = STRING_TOKEN;
                    sql->pos_strings[sql->n_strings++] = c_token-1;
                }
            }else{
                tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "c");
                sql->tokens[c_token++] = STRING_TOKEN;
                sql->pos_strings[sql->n_strings++] = c_token-1;
            }
        }
        else if (input[index] == 'i'){
            index++;
            if (input[index] == 'n'){
                index++;
                if (input[index] == 's'){
                    index++;
                    if (input[index] == 'e'){
                        index++;
                        if (input[index] == 'r'){
                            index++;
                            if (input[index] == 't'){
                                index++;
                                if (input[index] == ' '){
                                    sql->tokens[c_token++] = INSERT_TOKEN;
                                    index++;
                                }else{
                                    tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "insert");
                                    sql->tokens[c_token++] = STRING_TOKEN;
                                    sql->pos_strings[sql->n_strings++] = c_token-1;
                                }
                            }else{
                                tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "inser");
                                sql->tokens[c_token++] = STRING_TOKEN;
                                sql->pos_strings[sql->n_strings++] = c_token-1;
                            }
                        }else{
                            tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "inse");
                            sql->tokens[c_token++] = STRING_TOKEN;
                            sql->pos_strings[sql->n_strings++] = c_token-1;
                        }       
                    }else{
                        tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "ins");
                        sql->tokens[c_token++] = STRING_TOKEN;
                        sql->pos_strings[sql->n_strings++] = c_token-1;
                    }
                }else{
                    tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "in");
                    sql->tokens[c_token++] = STRING_TOKEN;
                    sql->pos_strings[sql->n_strings++] = c_token-1;
                }
            }else{
                tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "i");
                sql->tokens[c_token++] = STRING_TOKEN;
                sql->pos_strings[sql->n_strings++] = c_token-1;
            }
        }
        else if (input[index] == 'i'){
            index++;
            if (input[index] == 'n'){
                index++;
                if (input[index] == 't'){
                    index++;
                    if (input[index] == 'o'){
                        index++;
                        if (input[index] == ' '){
                            sql->tokens[c_token++] = INTO_TOKEN;
                            index++;
                        }else{
                            tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "into");
                            sql->tokens[c_token++] = STRING_TOKEN;
                            sql->pos_strings[sql->n_strings++] = c_token-1;
                        }
                    }else{
                        tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "int");
                        sql->tokens[c_token++] = STRING_TOKEN;
                        sql->pos_strings[sql->n_strings++] = c_token-1;
                    }
                }else{
                    tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "in");
                    sql->tokens[c_token++] = STRING_TOKEN;
                    sql->pos_strings[sql->n_strings++] = c_token-1;
                }
            }else{
                tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "i");
                sql->tokens[c_token++] = STRING_TOKEN;
                sql->pos_strings[sql->n_strings++] = c_token-1;
            }
        }
        else if (input[index] == 'u'){
            index++;
            if (input[index] == 'p'){
                index++;
                if (input[index] == 'd'){
                    index++;
                    if (input[index] == 'a'){
                        index++;
                        if (input[index] == 't'){
                            index++;
                            if (input[index] == 'e'){
                                index++;
                                if (input[index] == ' '){
                                    sql->tokens[c_token++] = UPDATE_TOKEN;
                                    index++;
                                }else{
                                    tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "update");
                                    sql->tokens[c_token++] = STRING_TOKEN;
                                    sql->pos_strings[sql->n_strings++] = c_token-1;
                                }
                            }else{
                                tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "updat");
                                sql->tokens[c_token++] = STRING_TOKEN;
                                sql->pos_strings[sql->n_strings++] = c_token-1;
                            }
                        }else{
                            tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "upda");
                            sql->tokens[c_token++] = STRING_TOKEN;
                            sql->pos_strings[sql->n_strings++] = c_token-1;
                        }       
                    }else{
                        tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "upd");
                        sql->tokens[c_token++] = STRING_TOKEN;
                        sql->pos_strings[sql->n_strings++] = c_token-1;
                    }
                }else{
                    tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "up");
                    sql->tokens[c_token++] = STRING_TOKEN;
                    sql->pos_strings[sql->n_strings++] = c_token-1;
                }
            }else{
                tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "u");
                sql->tokens[c_token++] = STRING_TOKEN;
                sql->pos_strings[sql->n_strings++] = c_token-1;
            }
        }
        else if (input[index] == 'd'){
            index++;
            if (input[index] == 'r'){
                index++;
                if (input[index] == 'o'){
                    index++;
                    if (input[index] == 'p'){
                        index++;
                        if (input[index] == ' '){
                            sql->tokens[c_token++] = DROP_TOKEN;
                            index++;
                        }else{
                            tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "drop");
                            sql->tokens[c_token++] = STRING_TOKEN;
                            sql->pos_strings[sql->n_strings++] = c_token-1;
                        }
                    }else{
                        tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "dro");
                        sql->tokens[c_token++] = STRING_TOKEN;
                        sql->pos_strings[sql->n_strings++] = c_token-1;
                    }
                }else{
                    tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "dr");
                    sql->tokens[c_token++] = STRING_TOKEN;
                    sql->pos_strings[sql->n_strings++] = c_token-1;
                }
            }else if (input[index]=='a'){
                index++;
                if (input[index] == 't'){
                    index++;
                    if (input[index] == 'a'){
                        index++;
                        if (input[index] == 'b'){
                            index++;
                            if (input[index] == 'a'){
                                index++;
                                if (input[index] == 's'){
                                    index++;
                                    if (input[index] == 'e'){
                                        index++;
                                        if (input[index] == ' '){
                                            sql->tokens[c_token++] = DATABASE_TOKEN;
                                            index++;
                                        }else{
                                            tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "database");
                                            sql->tokens[c_token++] = STRING_TOKEN;
                                            sql->pos_strings[sql->n_strings++] = c_token-1;
                                        }
                                    }else{
                                        tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "databas");
                                        sql->tokens[c_token++] = STRING_TOKEN;
                                        sql->pos_strings[sql->n_strings++] = c_token-1;
                                    }
                                }else{
                                    tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "databa");
                                    sql->tokens[c_token++] = STRING_TOKEN;
                                    sql->pos_strings[sql->n_strings++] = c_token-1;
                                }
                            }else{
                                tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "datab");
                                sql->tokens[c_token++] = STRING_TOKEN;
                                sql->pos_strings[sql->n_strings++] = c_token-1;
                            }
                        }else{
                            tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "data");
                            sql->tokens[c_token++] = STRING_TOKEN;
                            sql->pos_strings[sql->n_strings++] = c_token-1;
                        }
                    }else{
                        tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "dat");
                        sql->tokens[c_token++] = STRING_TOKEN;
                        sql->pos_strings[sql->n_strings++] = c_token-1;
                    }
                }else{
                    tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "da");
                    sql->tokens[c_token++] = STRING_TOKEN;
                    sql->pos_strings[sql->n_strings++] = c_token-1;
                }
            }else{
                tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "d");
                sql->tokens[c_token++] = STRING_TOKEN;
                sql->pos_strings[sql->n_strings++] = c_token-1;
            }
        }
        else if (input[index] == 'f'){
            index++;
            if (input[index] == 'r'){
                index++;
                if (input[index] == 'o'){
                    index++;
                    if (input[index] == 'm'){
                        index++;
                        if (input[index] == ' '){
                            sql->tokens[c_token++] = FROM_TOKEN;
                            index++;
                        }else{
                            tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "from");
                            sql->tokens[c_token++] = STRING_TOKEN;
                            sql->pos_strings[sql->n_strings++] = c_token-1;
                        }
                    }else{
                        tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "fro");
                        sql->tokens[c_token++] = STRING_TOKEN;
                        sql->pos_strings[sql->n_strings++] = c_token-1;
                    }
                }else{
                    tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "fr");
                    sql->tokens[c_token++] = STRING_TOKEN;
                    sql->pos_strings[sql->n_strings++] = c_token-1;
                }
            }else{
                tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "f");
                sql->tokens[c_token++] = STRING_TOKEN;
                sql->pos_strings[sql->n_strings++] = c_token-1;
            }
        }else if (input[index] == 't'){
            index++;
            if (input[index] == 'a'){
                index++;
                if (input[index] == 'b'){
                    index++;
                    if (input[index] == 'l'){
                        index++;
                        if (input[index] == 'e'){
                            index++;
                            if (input[index] == ' '){
                            sql->tokens[c_token++] = TABLE_TOKEN;
                                index++;
                            }else{
                                tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "table");
                                sql->tokens[c_token++] = STRING_TOKEN;
                                sql->pos_strings[sql->n_strings++] = c_token-1;
                            }
                        }else{
                            tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "tabl");
                            sql->tokens[c_token++] = STRING_TOKEN;
                            sql->pos_strings[sql->n_strings++] = c_token-1;
                        }
                    }else{
                        tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "tab");
                        sql->tokens[c_token++] = STRING_TOKEN;
                        sql->pos_strings[sql->n_strings++] = c_token-1;
                    }
                }else{
                    tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "ta");
                    sql->tokens[c_token++] = STRING_TOKEN;
                    sql->pos_strings[sql->n_strings++] = c_token-1;
                }
            }else{
                tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "t");
                sql->tokens[c_token++] = STRING_TOKEN;
                sql->pos_strings[sql->n_strings++] = c_token-1;
            }
        }
        else{
            // If none of the cases above, get string.
            tmp_string_pointers[tmp_string_index++] = capture_string(input, &index, "");
            sql->tokens[c_token++] = STRING_TOKEN;
            sql->pos_strings[sql->n_strings++] = c_token-1;
        }
    }
    return sql;
}


