#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include<arpa/inet.h>	//inet_addr

// https://www.binarytides.com/socket-programming-c-linux-tutorial/

// inet_addr("74.125.235.20"); Converts ip string to long

/*
struct sockaddr_in {
    short            sin_family;   // e.g. AF_INET, AF_INET6
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
};

struct in_addr {
    unsigned long s_addr;          // load with inet_pton()
};

struct sockaddr {
    unsigned short    sa_family;    // address family, AF_xxx
    char              sa_data[14];  // 14 bytes of protocol address
};

*/

int connect_to_socket(const char* ip, int port){
    struct sockaddr_in server;

    server.sin_addr.s_addr = inet_addr(ip);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0){
		// Unable to connect
		return 1;
	}
	return 0;
}

int send_data(struct sockaddr_in, char* data){
	if(send(socket_desc, message, strlen(data) , 0) < 0){
        // Unable to send data
		return 1;
	}
	return 0;

}
