#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <openssl/sha.h>

#define USER

typedef struct User{
    char name[256];
    char role[256];
    uint8_t hash[64]; // sha-512, 64 bytes, 128 hex chars if as a string 
} User;


uint8_t add_user(User* user){
    return 1;
}

uint8_t* return_hashed(char* input){
    uint8_t hash[64];
    if (SHA512_DIGEST_LENGTH != 64) printf("SHA512_DIGEST_LENGTH != 64\n");
    SHA512(input, strlen(input), hash);
    return &hash;
}