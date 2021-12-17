
#define SQL_PARSER_LENGTH 256
#define BUFFER_LENGTH 256

#define SQL_TOKEN_SELECT "select" 
#define SQL_TOKEN_FROM "from"
#define SQL_TOKEN_WHERE "where"


struct Sql_Expression{
    unsigned int * tokens;
    unsigned int n_tokens;
    char** strings;
    unsigned int n_strings;
    unsigned int* pos_strings;
};
typedef struct Sql_Expression Sql_Expression;

struct Sql_Parser{
    unsigned int tokens[SQL_PARSER_LENGTH];
    char** strings;
    unsigned int n_strings;
    unsigned int exp_type;
    unsigned int* pos_strings;
};
typedef struct Sql_Parser Sql_Parser;

struct Query{
    char* table;
    char** columns;
    int n_columns;
    //QUALIFIER* qualifier;
};
typedef struct Query Query;


typedef enum {
    STATE_INIT,
    STATE_SELECT,
    STATE_FROM,
    STATE_COMMA,
    STATE_SEMICOLON,
    STATE_ASTERISC,
    STATE_STRING,
    STATE_INVALID_CHAR
} State;

