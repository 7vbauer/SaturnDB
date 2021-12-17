/*
 *
 * TODO:
 * 	- Check the need for 'buffer' that keeps the current token.
 *	  I think the token_index is the only thing needed.
 *
 *
 * */

#include <stdint.h>
#include <ctype.h>

#include "SQLTokenizer.h"

int check_char(char c){
    if (isalpha(c) || c == '"' || c == '\'') 
        return 1;
    return 0;
}

Sql_Expression* parser(const char* text){
    State state = STATE_INIT;
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
		if(text[index] == SQL_TOKEN_SELECT[token_index + 1]){{
			
		}else{

		}
            case(STATE_ASTERISC):
            case(STATE_FROM):
            case(STATE_COMMA):
            case(STATE_SEMICOLON):
        }
        index++;
    }

}
