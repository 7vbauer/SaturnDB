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

char** flag_process(int argc, char* argv[]){
    uint8_t u = 0;
    uint8_t db = 0;
    uint8_t image = 1;
    
    for(int i = 0; i < argc; i++){
        if(argv[i] == "-u") u = i;
        if(argv[i] == "-db") db = i;
        if(argv[i] == "-noimage") image = 0;
    }

    if (u != 0){
        char* user = argv[u+1];
        char* password = get_password('Password: ');
        User* logged = check_credentials(user, get_user_salt(user),password);
        // All verifications must be done in the check credentials function.
        // Here, if logged if not NULL, it is guaranteed that it contains a 
        // valid user.
        if (logged != NULL){
            // Pass the info to the saturndb struct
            if (db != 0){
                // Try to select the db, if the user has privileges for it.
            }
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

    

    


}


