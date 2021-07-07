
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


// If The first token of the expression is SELECT and the expression
// itself is valid, call the function

// SELECT <column, > FROM <table> WHERE <...>
// At this point, the SQL_EXPRESSION 'e' is already into tokens.



// select col1, col2, col3 from table1

// 4      3   0  3  0  3    15  3

typedef struct SELECT_PARSER{
    char** targets;
    int n_targets;
    char* table;
    Qualifier* q;
    char* orderby;
};



Table* select(SQL_EXPRESSION s){
    unsigned int commas [s->n_tokens];
    unsigned int commas_ind = 0;
    for(int i = 0; i < s->n_tokens; i++){
        if(s->tokens[i] == COMMA_TOKEN)
            commas[commas_ind++] = i;
    }
    unsigned int n_attributes = commas_ind + 1;
    SELECT_PARSER* sp = malloc(sizeof(SELECT_PARSER));
    sp->targets = malloc(n_attributes * sizeof(char*));
    
    for(int i = 0; i < n_attributes - 1; i++){
        sp->targets[i] = s->strings[s->pos_strings[commas[i]-1]]
    }
    sp->n_targets = s->tokens[commas[commas_ind]] + 1
}
