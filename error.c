


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#define LOG_FILE "saturndb_logs.txt"

/*
    STANDARD BEHAVIOR IS TO LOG ACTION MSGS INTO THE LOG FILE
                        LOG ERROR MESSAGES BOTH IN LOG FILE AND ERROR
                        STD OUTPUT
*/

uint8_t log_action_msg(char* msg){

    f = open(LOG_FILE, "a")
    char text[strlen("ACTION\n" + strlen(msg)) + strlen("\n\n")];

    strcat(text, "ACTION\n");
    strcat(text, msg);
    strcat(text, "\n\n");

    fprint(f, text);

    fclose(f);   
    return (uint8_t) 1;
}


uint8_t log_error_msg(char* msg){

    f = open(LOG_FILE, "a")
    char text[strlen("ERROR\n" + strlen(msg)) + strlen("\n\n")];

    strcat(text, "ERROR\n");
    strcat(text, msg);
    strcat(text, "\n\n");

    fprint(f, text);
    fprint(stderr, text);

    fclose(f);   
    return (uint8_t) 1;
}


