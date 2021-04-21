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
    new_client->cdir = NULL;
    new_client->CMD = NULL;
    new_client->msg = NULL;
    new_client->parsing = NULL;
    client_t *ptr = *list_client;
    new_client->fd = fd_accept;
    // printf("client fd: %d\n", new_client->fd);
    add_message_to_list("Service ready for new user.", "220", &new_client->msg);
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
    // printf("QUIT NEW CLIENT CONNECTION\n");
}



int running_serv(int fd, char *dir)
{
    //sauvegarder le dir dans la struct du user ?
    client_t *list_client = NULL;
    int select_return;
    fd_set read_fds;
    fd_set write_fds;
    int fdmax = fd;
    if (listen(fd, 10) < 0) {
        return (84);
    }
    while(1) {
        check_read_fdset(&read_fds, &fdmax, fd, &list_client);
        //a utiliser + tard quand je vais devoir ecrire un message
        check_write_fdset(&write_fds, fd, &list_client);
        select_return = select(fdmax +1, &read_fds, &write_fds, NULL, NULL);
        if (select_return == - 1 && errno == EINTR)
            continue;
        if (select_return == -1) {
            return (84);
        }
        else if (FD_ISSET(fd, &read_fds))
            new_connection(&list_client, fd);
        check_client_write_file(&list_client, &write_fds);
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

//comprendre a quel moment il a fini d'ecrire son message
//utiliser un pointeurs a deplacer pour recuperer la srting en entier RFC
//
//faire parsing de ce qu'as eccrit le user
//faire tableau de pointeurs sur fonction
//faire une liste chainne des reponses a envoyer

//faire une structure message que je peux utiliser dans la structure
//client
//int et message, pour pouvoir repondre + facilement.
//
//tester

//faire un buffer de taille limite
//faire un enum pour le truc des users