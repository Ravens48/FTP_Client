/*
** EPITECH PROJECT, 2021
** myFtp
** File description:
** server
*/

#include "../includes/my_ftp.h"

int starting_serv(int port, int adress)
{
    struct sockaddr_in address;
    int socketfd;
    int yes = 1;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        perror("socket fd failed");
        exit(84);
    }
    //utile pour reutiliser un port
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);
    //mettre une garde ?
    if (bind(socketfd,(const struct sockaddr *)&address, sizeof(struct sockaddr_in)) == 1)
        return (84);
    //peut etre mettre avant le select
    return socketfd;
}

void set_up_new_client(client_t *new_client, int fd_accept, char* dir)
{
    new_client->cdir = dir;
    new_client->parent_dir = dir;
    new_client->CMD = NULL;
    new_client->msg = NULL;
    new_client->parsing = NULL;
    new_client->state = UNKNOW;
    new_client->valid_user = 0;
    new_client->fd = fd_accept;
} 

void new_connection(client_t **list_client, int fd, char *dir)
{
    struct sockaddr_in address;
    socklen_t adrlen = sizeof(struct sockaddr_in);
    int fd_accept;                                                                                                                        
    if ((fd_accept = accept(fd, (struct sockaddr *)&address, &adrlen)) == -1) {
        return;
    }
    printf("NEW CLIENT CONNECTION\n");
    client_t * new_client = malloc(sizeof(client_t));
    set_up_new_client(new_client, fd_accept, dir);
    client_t *ptr = *list_client;
    add_message_to_list("Service ready for new user.", "220", &new_client->msg);
    // new_client->path
    new_client->next = NULL;
    if (ptr == NULL) {
        *list_client = new_client;
        return;
    }
    while(ptr->next != NULL) {
        ptr = ptr->next;
    }
    ptr->next = new_client;
}



int running_serv(int fd, char *dir)
{
    client_t *list_client = NULL;
    int select_return;
    fd_set read_fds;
    fd_set write_fds;
    int fdmax = fd;
    if (listen(fd, 10) < 0)
        return (84);
    while(1) {
        check_read_fdset(&read_fds, &fdmax, fd, &list_client);
        //a utiliser + tard quand je vais devoir ecrire un message
        check_write_fdset(&write_fds, fd, &list_client);
        select_return = select(fdmax +1, &read_fds, &write_fds, NULL, NULL);
        if (select_return == - 1 && errno == EINTR)
            continue;
        if (select_return == -1)
            return (84);
        else if (FD_ISSET(fd, &read_fds))
            new_connection(&list_client, fd, dir);
        check_client_write_file(&list_client, &write_fds);
        check_client_file(&list_client, &read_fds);
    }
    close(fd);
}
