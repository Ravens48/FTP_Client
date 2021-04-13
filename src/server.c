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
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEPORT | SO_REUSEADDR, NULL, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);
    //mettre une garde ?
    if (bind(socketfd,(const struct sockaddr *)&address, sizeof(struct sockaddr_in)) == 1)
        return (84);
    //peut etre mettre avant le select
    return socketfd;
}

void new_connection(client_t **list_client, int fd)
{
    struct sockaddr_in address;
    socklen_t adrlen = sizeof(struct sockaddr_in);
    int fd_accept;                                                                                                                        
    if ((fd_accept = accept(fd, (struct sockaddr *)&address, &adrlen)) == -1) {
        return;
    }
    printf("NEW CLIENT CONNECTION\n");
    client_t * new_client = malloc(sizeof(client_t));
    client_t *ptr = *list_client;
    new_client->fd = fd_accept;
    // new_client->path
    new_client->next = NULL;
    printf("%d\n", new_client->fd);
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


void check_allfdset(fd_set *fds, int *fdmax, int fd, client_t **list_client)
{
    //remet a zero
    FD_ZERO(fds);
    FD_SET (fd, fds);
    client_t *ptr = *list_client;


    //boucle sur les clients ajoute avec FD_Set un nouveau fd
    // et on compare pour changer la taille de fdmax le cas echeant
    while(ptr != NULL) {
        FD_SET (ptr->fd, fds);
        if (*fdmax < ptr->fd)
                *fdmax = ptr->fd;
        ptr = ptr->next;
    }
}

void check_client_file(client_t **list_client, fd_set *read_fds)
{
    //boucler read sur les fichier des users
    client_t *ptr = *list_client;
    while(ptr != NULL) {
        if (FD_ISSET(ptr->fd, read_fds)) {
            ptr->CMD = malloc(sizeof(char)* 128);
            if (read(ptr->fd, ptr->CMD, 128) == -1)
                return;
            printf("%s\n", ptr->CMD);
        }
        ptr = ptr->next;
    }
}

int running_serv(int fd, char *dir)
{
    client_t *list_client = NULL;
    int select_return;
    fd_set read_fds;
    fd_set write_fds;
    int fdmax = fd;
    if (listen(fd, 10) < 0) {
        return (84);
    }
    while(1) {
        check_allfdset(&read_fds, &fdmax, fd, &list_client);
        // check_allfdset(&write_fds, &fdmax, fd, &list_client);
        select_return = select(fdmax +1, &read_fds, NULL, NULL, NULL);
        if (select_return == - 1 && errno == EINTR)
            continue;
        if (select_return == -1) {
            return (84);
        }
        else if (FD_ISSET(fd, &read_fds))
            new_connection(&list_client, fd);
        check_client_file(&list_client, &read_fds);
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


/*
fd_set rfds -> un tableau de fd
dans la boucle
FD_ZERO(rfds) -> remet le tableau a nul
FD_set -> socket du server, 
selet monitor les changement sur le tbleau et te dis ce qui est touhcer
et renvoie un tableau juste avec les fd modifier et ce qui est pret a etre lu
*/

/*
pass a pointer index
*/

//faire parsing
//faire tableau de pointeurs sur fonction
//tester