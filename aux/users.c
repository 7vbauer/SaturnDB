#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <openssl/sha.h>
#include <termios.h>
#include "expressions/exp.c"
// ADD THE GARBAGE COLLECTOR #include <gc.h>
// FOR COMPARING STRING NEED TO USE STRCMP'OR STRNCMP

#define USER_FILE "saturn_access.txt"

// REALLOC EXTREMELY USEFULLLLLLL

char* get_password(char* msg);
FILE* open_file_read(void);
FILE* open_file_write(void);
uint8_t add_user(User* user);
uint8_t* return_hashed(char* input);
char* get_user_string(char* name);
char** parse_user_string(char* line, uint8_t size);


typedef struct User{
    char name[256];
    char role[256];
    uint8_t hash[64]; // sha-512, 64 bytes, 128 hex chars if as a string 
} User;

typedef struct AccessFile{
    char** lines;
    uint8_t n_lines;
}AccessFile;

char* get_password(char* msg){
    // https://stackoverflow.com/questions/1786532/c-command-line-password-input
    // thanks s2
    char* password[BUFFER_SIZE];
    printf(msg);
    static struct termios o_term;
    static struct termios n_term;
    tcgetattr(STDIN_FILENO, &old_terminal);

    n_term = o_term;
    n_term.c_lflag &= ~(ECHO);

    tcseattr(STDIN_FILENO, TCSANOW, &n_term);

    // BUFFER_SIZE defined in exp.c
    if(fgets(password, BUFFER_SIZE, stdin) == NULL)
        password[0] = '\0';
    else
        password[strlen(password) - 1] = '\0';

    tcseattr(STDIN_FILENO, TCSANOW, &o_term);

    return password;
}

FILE* open_file_read(void){
    FILE* f = fopen(USER_FILE, "r");
    if (f == NULL){
        return NULL;
        //Treat the errors
    }
    return f;
}

FILE* open_file_write(void){
    FILE* f = fopen(USER_FILE, "a");
    if (f == NULL){
        return NULL;
        //Treat the errors
    }
    return f;
}

uint8_t check_existing_user(char* name){
    FILE* f = open_file_read();

}

uint8_t add_user(User* user){
    uint8_t exists = check_existing_user(user->name);
    if (exists == 1){
        //Warning that user already exists
        return 0;
    }
    
    return 1;
}



uint8_t* return_hashed(char* input){
    uint8_t hash[64];
    if (SHA512_DIGEST_LENGTH != 64) printf("SHA512_DIGEST_LENGTH != 64\n");
    SHA512(input, strlen(input), hash);
    return &hash;
}

uint8_t check_credentials(char* user, uint8_t* hashed){
    return 1;
    return 0;
}

char* get_user_salt(char* username){
    return NULL;
}

/*

snprintf and vsnprintf

*/


char* get_user_string(char* name){
    // https://stackoverflow.com/questions/3501338/c-read-file-line-by-line

    FILE* fp = open_file_read();
    FILE* fp2 = *fp; // Need of getting back to the beginning, later use.
    char * line = NULL;
    // type of the result returned by sizeof operator, unsigned integer
    size_t len = 0;
    // same as size_t but signed
    ssize_t read;

    uint8_t n_lines = 0;
    while(read = getline(&line, &len, fp)) != -1)
        n_lines++;

    char** file_lines = malloc(n_lines * sizeof(char*));

    // Gets the pointer back to the beginning of the file;
    fp = fp2;
    n_lines = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        // %zu specifies the value from size_t type
        // read => number of letters in line
        // line => string containing the line
        char* tmp = malloc(read * sizeof(char) + 1);
        strcpy(tmp, line);
        tmp[read + 1] = '\0';
        file_lines[n_lines] = tmp;
        n_lines++;
    }
    fclose(fp);

    AccessFile* acc = malloc(sizeof(AccessFile));
    // AccessFile is a struct to auxiliate the user string management
    // 
    acc->lines = lines;
    acc->n_lines = n_lines;
    return acc;

    // AccessFile* 
}

char** parse_user_string(char* line, uint8_t size){
    uint8_t v[4];
    uint8_t v_ind = 0;
    for (int i = 0; i < size; i++)
        if (line[i] == ':')
            v[v_ind++]=i;
    char** data = malloc(4 * sizeof(char*));

    uint8_t k = 0
    while(k < 4){
        if (k == 0){
            char* word = malloc(v[0] * sizeof(char) + 1);
            strncpy(word, &line[0], v[1]);
            word[v[0]] = '\0';
        }else{
            char* word = malloc((v[k] - v[k-1]) * sizeof(char) + 1);
            strncpy(word, &line[v[k-1]+1], v[k]);
            word[v[k] - v[k-1]] = '\0';  
        }
        data[k] = word;
        k++;
    }
    // 'data' should contain the info from the access file, <name : role : salt : hash> ending with '\0'
    return data;
    
}

    // BUFFER_SIZE defined in exp.c
    if(fgets(password, BUFFER_SIZE, stdin) == NULL)
        password[0] = '\0';
    else
        password[strlen(password) - 1] = '\0';

    tcseattr(STDIN_FILENO, TCSANOW, &o_term);

    return password;
}

FILE* open_file_read(void){
    FILE* f = fopen(USER_FILE, "r");
    if (f == NULL){
        return NULL;
        //Treat the errors
    }
    return f;
}

FILE* open_file_write(void){
    FILE* f = fopen(USER_FILE, "a");
    if (f == NULL){
        return NULL;
        //Treat the errors
    }
    return f;
}

uint8_t check_existing_user(char* name){
    FILE* f = open_file_read();

}

uint8_t add_user(User* user){
    uint8_t exists = check_existing_user(user->name);
    if (exists == 1){
        //Warning that user already exists
        return 0;
    }
    
    return 1;
}



uint8_t* return_hashed(char* input){
    uint8_t hash[64];
    if (SHA512_DIGEST_LENGTH != 64) printf("SHA512_DIGEST_LENGTH != 64\n");
    SHA512(input, strlen(input), hash);
    return &hash;
}

uint8_t check_credentials(char* user, uint8_t* hashed){
    return 1;
    return 0;
}

char* get_user_salt(char* username){
    return NULL;
}

/*

snprintf and vsnprintf

*/


char* get_user_string(char* name){
    // https://stackoverflow.com/questions/3501338/c-read-file-line-by-line

    FILE* fp = open_file_read();
    FILE* fp2 = *fp;
    char * line = NULL;
    // type of the result returned by sizeof operator, unsigned integer
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <openssl/sha.h>
#include <termios.h>
#include "expressions/exp.c"
// ADD THE GARBAGE COLLECTOR #include <gc.h>
// FOR COMPARING STRING NEED TO USE STRCMP'OR STRNCMP

#define USER_FILE "saturn_access.txt"

// REALLOC EXTREMELY USEFULLLLLLL

char* get_password(char* msg);
FILE* open_file_read(void);
FILE* open_file_write(void);
uint8_t add_user(User* user);
uint8_t* return_hashed(char* input);
char* get_user_string(char* name);
char** parse_user_string(char* line, uint8_t size);


typedef struct User{
    char name[256];
    char role[256];
    uint8_t hash[64]; // sha-512, 64 bytes, 128 hex chars if as a string 
} User;

typedef struct AccessFile{
    char** lines;
    uint8_t n_lines;
}AccessFile;

char* get_password(char* msg){
    // https://stackoverflow.com/questions/1786532/c-command-line-password-input
    // thanks s2
    char* password[BUFFER_SIZE];
    printf(msg);
    static struct termios o_term;
    static struct termios n_term;
    tcgetattr(STDIN_FILENO, &old_terminal);

    n_term = o_term;
    n_term.c_lflag &= ~(ECHO);

    tcseattr(STDIN_FILENO, TCSANOW, &n_term);

    // BUFFER_SIZE defined in exp.c
    if(fgets(password, BUFFER_SIZE, stdin) == NULL)
        password[0] = '\0';
    else
        password[strlen(password) - 1] = '\0';

    tcseattr(STDIN_FILENO, TCSANOW, &o_term);

    return password;
}

FILE* open_file_read(void){
    FILE* f = fopen(USER_FILE, "r");
    if (f == NULL){
        return NULL;
        //Treat the errors
    }
    return f;
}

FILE* open_file_write(void){
    FILE* f = fopen(USER_FILE, "a");
    if (f == NULL){
        return NULL;
        //Treat the errors
    }
    return f;
}

uint8_t check_existing_user(char* name){
    FILE* f = open_file_read();

}

uint8_t add_user(User* user){
    uint8_t exists = check_existing_user(user->name);
    if (exists == 1){
        //Warning that user already exists
        return 0;
    }
    
    return 1;
}



uint8_t* return_hashed(char* input){
    uint8_t hash[64];
    if (SHA512_DIGEST_LENGTH != 64) printf("SHA512_DIGEST_LENGTH != 64\n");
    SHA512(input, strlen(input), hash);
    return &hash;
}

uint8_t check_credentials(char* user, uint8_t* hashed){
    return 1;
    return 0;
}

char* get_user_salt(char* username){
    return NULL;
}

/*

snprintf and vsnprintf

*/


char* get_user_string(char* name){
    // https://stackoverflow.com/questions/3501338/c-read-file-line-by-line

    FILE* fp = open_file_read();
    FILE* fp2 = *fp; // Need of getting back to the beginning, later use.
    char * line = NULL;
    // type of the result returned by sizeof operator, unsigned integer
    size_t len = 0;
    // same as size_t but signed
    ssize_t read;

    uint8_t n_lines = 0;
    while(read = getline(&line, &len, fp)) != -1)
        n_lines++;

    char** file_lines = malloc(n_lines * sizeof(char*));

    // Gets the pointer back to the beginning of the file;
    fp = fp2;
    n_lines = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        // %zu specifies the value from size_t type
        // read => number of letters in line
        // line => string containing the line
        char* tmp = malloc(read * sizeof(char) + 1);
        strcpy(tmp, line);
        tmp[read + 1] = '\0';
        file_lines[n_lines] = tmp;
        n_lines++;
    }
    fclose(fp);

    AccessFile* acc = malloc(sizeof(AccessFile));
    // AccessFile is a struct to auxiliate the user string management
    // 
    acc->lines = lines;
    acc->n_lines = n_lines;
    return acc;

    // AccessFile* 
}

char** parse_user_string(char* line, uint8_t size){
    uint8_t v[4];
    uint8_t v_ind = 0;
    for (int i = 0; i < size; i++)
        if (line[i] == ':')
            v[v_ind++]=i;
    char** data = malloc(4 * sizeof(char*));

    uint8_t k = 0
    while(k < 4){
        if (k == 0){
            char* word = malloc(v[0] * sizeof(char) + 1);
            strncpy(word, &line[0], v[1]);
            word[v[0]] = '\0';
        }else{
            char* word = malloc((v[k] - v[k-1]) * sizeof(char) + 1);
            strncpy(word, &line[v[k-1]+1], v[k]);
            word[v[k] - v[k-1]] = '\0';  
        }
        data[k] = word;
        k++;
    }
    // 'data' should contain the info from the access file, <name : role : salt : hash> ending with '\0'
    return data;
    
}
