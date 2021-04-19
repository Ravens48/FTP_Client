/*
** EPITECH PROJECT, 2021
** myFtp
** File description:
** checking_function
*/

#include "../includes/my_ftp.h"

void check_allfdset(fd_set *fds, int *fdmax, int fd, client_t **list_client)
{
    //remet a zero
    FD_ZERO(fds);
    //on remet tout et pour le write uniquement quand il y a un message a envoyer
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

void check_write_fdset(fd_set *fds, int fd, client_t **list_client, message_t **list_message)
{
    //remet a zero
    FD_ZERO(fds);
    // pour le write uniquement quand il y a un message a envoyer
    client_t *ptr = *list_client;
    message_t *ptr_message = *list_message;



    while(ptr != NULL && ptr_message != NULL) 
        {
            FD_SET (ptr->fd, fds);
        ptr = ptr->next;
    }

}

void check_client_file(client_t **list_client, fd_set *read_fds)
{
    //boucler read sur les fichier des users
    client_t *ptr = *list_client;
    // si le read retourne zero delete le client
    while(ptr != NULL) {
        if (FD_ISSET(ptr->fd, read_fds)) {
            ptr->CMD = malloc(sizeof(char)* 1024);
            if (read(ptr->fd, ptr->CMD, 1024) <= 0)
            //supprimer element de la liste mais continuer
            //ah oui on parle de delete le client ici
                return;
            printf("%s\n", ptr->CMD);
        }
        ptr = ptr->next;
    }
}

void check_client_write_file(client_t **list_client, fd_set *write_fds, message_t **list_message)
{
    //boucle infini dans le write check quand je quitte
    //liste de message vide rien a envoyer
    client_t *ptr = *list_client;
    message_t *ptr_message = *list_message;
    while(ptr != NULL) {
        if (FD_ISSET(ptr->fd, write_fds) && ptr_message != NULL) {
            // printf("check client : %s, fdclient:%d", ptr_message->message, ptr->fd);
            send_message_to_client(ptr->fd, ptr_message->message, ptr_message->code);
            list_message = pop_message(list_message);
            return;
        }
        ptr = ptr->next;
    }
}