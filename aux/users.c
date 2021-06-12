#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <openssl/sha.h>
#include <termios.h>
#include "expressions/exp.c"

#define USER_FILE "saturn_access.txt"

typedef struct User{
    char name[256];
    char role[256];
    uint8_t hash[64]; // sha-512, 64 bytes, 128 hex chars if as a string 
} User;

uint8_t* get_password(char* msg){
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

    return &password;
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

void* check_credentials(char* user, uint8_t* hashed){
    return NULL;
}

char* get_user_salt(char* username){
    return NULL;
}