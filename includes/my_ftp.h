/*
** EPITECH PROJECT, 2021
** myFtp
** File description:
** my_ftp
*/

#ifndef MY_FTP_H_
#define MY_FTP_H_

#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>

/*liste chainne pour le client

//pacours 

cleint *ptr = head;
while head != null

//fonction init

*/
typedef struct client {
    int fd;
    char *path;
    struct client *next;
} client_t;

int main();
void helper();

//create socket return fd for select;
int starting_serv(int, int);

//running serv with select
int running_serv(int fd);
int error_handle(int ac, char **av);

//client
//new connection
void new_connection(client_t**, int fd);
void check_allfdset(fd_set *read_fds, int *fdmax, int fd, client_t **list_client);

#endif /* !MY_FTP_H_ */
