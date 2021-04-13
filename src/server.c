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

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        perror("socket fd failed");
        exit(84);
    }
    //utile pour reutiliser un port
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEPORT, NULL, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);
    //mettre une garde ?
    bind(socketfd,(const struct sockaddr *)&address, sizeof(struct sockaddr_in));
    //peut etre mettre avant le select
    return socketfd;
}

void new_connection(client_t **list_client, int fd)
{
    client_t * new_client = malloc(sizeof(client_t));
    client_t *ptr = *list_client;
    new_client->fd = fd;
    // new_client->path
    new_client->next = NULL;
    //boucler dans la liste et ajouter un client
    if (ptr == NULL) {
        *list_client = new_client;
        return;
    }
    while(ptr->next != NULL) {
        //tojours derniere ligne
        ptr = ptr->next;
    }
    ptr->next = new_client;
}

void check_allfdset(fd_set *read_fds, int *fdmax, int fd, client_t **list_client)
{
    //remet a zero
    FD_ZERO(read_fds);
    FD_SET (fd, read_fds);
    client_t *ptr = *list_client;

    //boucle sur les clients ajoute avec FD_Set un nouveau fd
    // et on compare pour changer la taille de fdmax le cas echeant
    while(ptr != NULL) {
        FD_SET (ptr->fd, read_fds);
        if (*fdmax < ptr->fd)
                *fdmax = ptr->fd;
        ptr->next;
    }

}

int running_serv(int fd)
{
    client_t *list_client = NULL;
    int select_return;
    if (listen(fd, 10) < 0) {
        perror("listen failed");
        exit(84);
    }
    while(1) {
        fd_set read_fds;
        int fdmax = fd;
        check_allfdset(&read_fds, &fdmax, fd, &list_client);
        select_return = select(fdmax +1, &read_fds, NULL, NULL, NULL);
        if (select_return == - 1 && errno == EINTR)
            continue;
        if (select_return == -1) {
            perror("Select failed");
            return 84;
        }
        if (FD_ISSET(fd, &read_fds) != -1)
            new_connection(&list_client, fd);
    }
    close(fd);
}

//utiliser bind
//setsockpot
//man 2 bind
//FDISSET man 2 select donne si on a la valeur du socket creee
//si c'est le cas il s'agit d;une nouvelle connection
//INADRNI
//EINTR