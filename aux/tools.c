
#include <string.h>
#include <stdlib.h>

typedef struct list{
    char** items;
    int n_items;
} list;

#define SPLIT_BUFFER_SIZE 256

// Target string must end with \0
// function to ease the user string parsing.
// So far only accepts delimiter of length 1, single char
list* split(char* text, char x){
    list* l = malloc(sizeof(list));
    char bff[SPLIT_BUFFER_SIZE];
    for(int i = 0; i < SPLIT_BUFFER_SIZE; i++)
        bff[i] = '\0';

    int bff_ind = 0;
    for(int i = 0; i < strlen(text); i++){
        if (text[i] == x){
            bff_ind
        }

        bff[bff_ind] = 
    }

    return l;
}

char* join(){

}

void free_list(list* l){
    for(int i = 0; l->n_items; i++)
        free(l->items[i]);
    free(l);
}