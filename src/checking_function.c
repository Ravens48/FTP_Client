/*
** EPITECH PROJECT, 2021
** myFtp
** File description:
** checking_function
*/

#include "../includes/my_ftp.h"

void check_read_fdset(fd_set *fds, int *fdmax, int fd, client_t **list_client)
{
    //remet a zero
    FD_ZERO(fds);
    //on remet tout et pour le write uniquement quand il y a un message a envoyer
    FD_SET (fd, fds);
    client_t *ptr = *list_client;

    // printf("JE PASSE DANS LE READ FDSET\n");
    //boucle sur les clients ajoute avec FD_Set un nouveau fd
    // et on compare pour changer la taille de fdmax le cas echeant
    while(ptr != NULL) {
        FD_SET (ptr->fd, fds);
        if (*fdmax < ptr->fd)
                *fdmax = ptr->fd;
        ptr = ptr->next;
    }
    // printf("SORT DE READ FDSET\n");
}

void check_write_fdset(fd_set *fds, int fd, client_t **list_client)
{
    // printf("JE PASSE DANS LE CHECKWRITE\n");
    //remet a zero
    FD_ZERO(fds);
    // pour le write uniquement quand il y a un message a envoyer
    client_t *ptr = *list_client;
    // message_t *ptr->msg = *list_message;
    while(ptr != NULL)
        {
        // printf("Client FD: %d\n", ptr->fd);
        if (ptr->msg != NULL)
            FD_SET (ptr->fd, fds);
        ptr = ptr->next;
    }
    // printf("JE QUITTE LE CHECKWRITE\n");
}

void check_client_file(client_t **list_client, fd_set *read_fds)
{
    // printf("JE PASSE DANS LE CHECKCLIENT\n");
    //boucler read sur les fichier des users
    client_t *ptr = *list_client;
    client_t *temp = NULL;
    int r_read = 0;
    // si le read retourne zero delete le client
    while(ptr != NULL) {
        if (FD_ISSET(ptr->fd, read_fds)) {
            ptr->CMD = malloc(sizeof(char)* 1024);
            if (((r_read = read(ptr->fd, ptr->CMD, 1024)) <= 0) || ptr->state == DISCONNECT) 
            {
                temp = ptr->next;
                close(ptr->fd);
                search_and_destroy(list_client, ptr->fd);
                ptr = temp;
                continue;
            }
            //boucler trouver le meme pointeur et supprimer
            //supprimer element de la liste mais continue
            //close la socket du client
            //ah oui on parle de delete le client ici
        //    printf("%s\n", ptr->CMD);
            ptr->CMD[r_read] = '\0';
            parsing_fd_receive(ptr->CMD, &ptr->parsing, ptr);
        }
        ptr = ptr->next;
    }
    // printf("JE QUITTE LE CHECKCLIENT\n");

}

void check_client_write_file(client_t **list_client, fd_set *write_fds)
{
    printf("JE PASSE DANS LE CHECKWRITEFILE\n");
    //boucle infini dans le write check quand je quitte
    //liste de message vide rien a envoyer
    client_t *ptr = *list_client;
    // message_t *ptr_message = *list_message;
    while(ptr != NULL) {
//    printf("fdclient in write: %d\n", ptr->fd);
        if (FD_ISSET(ptr->fd, write_fds) && ptr->msg != NULL) {
            send_message_to_client(ptr->fd, ptr->msg->message, ptr->msg->code);
            pop_message(&ptr->msg);
        }
        printf("FD CLIENT IN WRITE: %d\n", ptr->fd);
        ptr = ptr->next;
    }
    // printf("JE QUITTE LE CHECKWRITEFILE\n");
}