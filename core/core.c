/*



select
create
insert
update
delete
drop



databases
tables
attributes
tuples



databases = database <x>, database back, drop <x>

table = table <x>, drop <x>



pwd = \db\table


"SELECT", "CREATE", "UPDATE", "DELETE", "DROP", "ALTER", "TABLE", "INDEX"

""


select table
insert 
create table/db
update table
delete data
drop table/db

https://www.easysoft.com/developer/languages/c/odbc_tutorial.html

technically SGBD use ODBC


DATA:

INT
LONG
DOUBLE
CHAR <X>








*/

#ifdef linux
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#endif

#include <stdint.h>
#include <stdio.h>
#include <sql.h>
#include <sqlext.h>
#include "aux/users.c"

typedef struct SaturnDB{
    char user_logged[256];
    char user_looged_role[256];
    char db_selected[256];
    uint16_t port;
    uint8_t installed;
    uint8_t terminal_width;
}SaturnDB;

char** flag_process(int argc, char* argv[], SaturnDB* s){
    uint8_t u = 0;
    uint8_t db = 0;
    uint8_t image = 1;
    
    for(int i = 0; i < argc; i++){
        // Rewrite with strcmp
        if(argv[i] == "-u") u = i;
        if(argv[i] == "-db") db = i;
        if(argv[i] == "-noimage") image = 0;
    }

    if (u != 0){// if the user flag was passed
        char* user = argv[u+1];
        char** ui = get_user_string(user);
        if (ui == NULL) return NULL;
        char* password = get_password("Password: ");
        char** cred = check_credentials(user, get_user_salt(user),password);
        if (cred == NULL) return NULL;
        // If cred is not NULL it returns the name and role of the authenticated user
        // All verifications must be done in the check credentials function.
        // Here, if logged is not NULL, it is guaranteed that it contains a 
        // valid user.
        s->user_logged = cred[0];
        s->user_looged_role = cred[1];
        if (db != 0){
            char* db_exists = check_db(argv[db+1]);
            if (db_exists == NULL){
                // Prints that database provided doenst exist or can't be accessed with current user.
            }else{
                s->db = argv[db+1];
            }
            // Try to select the db, if the user has privileges for it.
        }
    }
}

void init_saturdb(SaturnDB* sdb){
    sdb->user_logged = "\0";
    sdb->user_looged_role = "\0";
    sdb->db_selected = "\0";
    sdb->port = (uint16_t) 0;
    sdb->installed = (uint8_t) 0;
    sdb->terminal_width = (uint8_t) 0;
}

    char user_logged[256];
    char user_looged_role[256];
    char db_selected[256];
    uint16_t port;
    uint8_t installed;
    uint8_t terminal_width;



int main(int argc, char* argv[]){
    SaturnDB* saturndb = malloc(sizeof(SaturnDB));

    // Check Installation
    // If not installed, initiate the installation
    // otherwise, load installation info into saturndb struct


    // Gets the terminal window width.
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    saturndb->terminal_width = (uint8_t)w.ws_col;
    // w.ws_col and w.ws_row
    // Print the saturn ascii art

    // Check if installed

    // If not installed, install in the current directory, folder SaturnDB
    // Add to local path, so its possible to execute from anywhere.
    uint8_t installed = check_installation();

    if(installed == 0){
        // Checks if the user wants to install saturndb.
        // If so, runs script
        // Otherwise closes finishes execution and return.

        // Installation should get: root password, port to work on,   
        install_saturndb();
        return 0;
    }

    s->port = get_port()

    char** p_flags =  flag_process(argc, argv);


    // If Installed...
    // check if user provided



    // Begin loop
    // possible commands are only for the db, no sql yet until database selected

    // Create a buffer that will be reused until the db turns off.
    // In the loop, 
    while(1){
        //
    }


    
}



