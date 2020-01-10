#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define LENGTH 2048
#include <iostream>
using namespace std;
class conexion
{

// Global variables
public:
    volatile sig_atomic_t flag = 0;
    int sockfd = 0;
    char name[32];
    char ip[32] = "127.0.0.1";
    int port = 7777;
    struct sockaddr_in server_addr;
public:
    void catch_ctrl_c_and_exit(int);
    void str_overwrite_stdout();
    void str_trim_lf (char*, int);

    conexion();
   
    void conecta();
};

conexion::conexion()
{   sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);

}

void conexion::conecta(){
 int err = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (err == -1) {
		printf("ERROR: connect\n");
		//return EXIT_FAILURE;
	}
}


void conexion::str_overwrite_stdout()
{
    printf("%s", "> ");
    fflush(stdout);
}

void conexion::str_trim_lf(char* arr, int length)
{
    int i;
    for (i = 0; i < length; i++)   // trim \n
    {
        if (arr[i] == '\n')
        {
            arr[i] = '\0';
            break;
        }
    }
}

void conexion::catch_ctrl_c_and_exit(int sig)
{
    flag = 1;

}




#endif // CLIENTE_H_INCLUDED
