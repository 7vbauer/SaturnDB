#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#define SOCKET_REPLY_SIZE 1024

// https://www.binarytides.com/socket-programming-c-linux-tutorial/

int create_socket(void){
    int socket = socket(AF_INET, SOCK_STREAM, 0);
    //             IPV4  -TCP oriented - IP Protocol
    //                    'SOCK_DGRAM indicates UPD'
    if (socket == -1){
        // Socket not created
        // Error
        return -1;
    }
    return socket;
}

char* receive(int socket){
    char reply[SOCKET_REPLY_SIZE];
	if(recv(socket, server_reply, SOCKET_REPLY_SIZE, 0) < 0){
		// Receive failed ? Nothing to receive ?
        return 1;
	}
	return &reply;
}

// Somewhat useless, but keeps the syntax close to the other ones.
void close_socket(int socket){
    close(socket);
}
