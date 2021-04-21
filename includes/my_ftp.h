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
#include <dirent.h>
#include <sys/select.h>

/*liste chainne pour le client

//pacours 

cleint *ptr = head;
while head != null

//fonction init

*/
typedef struct message {
    char* code;
    char *message;
    struct message *next;
} message_t;

typedef struct parse {
    char *commande;
    char *args;
    struct parse *next;
} parse_t;

typedef struct client {
    int fd;
    char *cdir;
    char *CMD;
    struct client *next;
    message_t *msg;
    parse_t *parsing;
} client_t;


int main(int ac, char **av);
void helper();

//create socket return fd for select;
int starting_serv(int, int);

//running serv with select
int running_serv(int fd, char *directory);
int error_handle(int ac, char **av);

//message
//write messages

//a utiliser directement dans le retour des fonctions definies plus tard pour ajouter le message
//penser a clear la liste chainee une fois le message envoye
void add_message_to_list(char * message, char* code, message_t **list_msg);

void send_message_to_client(int fd, char *message, char* code);
void save_message_to_send();

//client
//new connection
void new_connection(client_t**, int fd);

//check
void check_client_file(client_t **list_client, fd_set *read_fds);
void check_read_fdset(fd_set *read_fds, int *fdmax, int fd, client_t **list_client);
void check_client_write_file(client_t **list_client, fd_set *write_fds);
void check_write_fdset(fd_set *fds, int fd, client_t **list_client);

//helper
void *pop_message(message_t **list_msg);
void search_and_destroy(client_t **list_client, int client_fd);
void pop_client(client_t **list_client, client_t *delete_client);
void free_my_client(client_t *client);
void free_my_message(message_t *message);
void free_my_parse(parse_t *parse);
void parsing_fd_receive(char *cmd, parse_t **parsing);
#endif /* !MY_FTP_H_ */
