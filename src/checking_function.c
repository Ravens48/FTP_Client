/*
** EPITECH PROJECT, 2021
** myFtp
** File description:
** checking_function
*/

#include "../includes/my_ftp.h"

void check_read_fdset(fd_set *fds, int *fdmax, int fd, client_t **list_client)
{
    FD_ZERO(fds);
    FD_SET (fd, fds);
    client_t *ptr = *list_client;

    while(ptr != NULL) {
        FD_SET (ptr->fd, fds);
        if (*fdmax < ptr->fd)
                *fdmax = ptr->fd;
        ptr = ptr->next;
    }
}

void check_write_fdset(fd_set *fds, int fd, client_t **list_client)
{
    FD_ZERO(fds);
    client_t *ptr = *list_client;
    while(ptr != NULL)
        {
        if (ptr->msg != NULL)
            FD_SET (ptr->fd, fds);
        ptr = ptr->next;
    }
}

void check_client_file(client_t **list_client, fd_set *read_fds)
{
    client_t *ptr = *list_client;
    client_t *temp = NULL;
    int r_read = 0;
    while(ptr != NULL) {
        if (FD_ISSET(ptr->fd, read_fds)) {
            ptr->CMD = malloc(sizeof(char)* 1024);
            if (((r_read = read(ptr->fd, ptr->CMD, 1024)) <= 0)) 
            {
                temp = ptr->next;
                close(ptr->fd);
                search_and_destroy(list_client, ptr->fd);
                ptr = temp;
                continue;
            }
            ptr->CMD[r_read] = '\0';
            parsing_fd_receive(ptr->CMD, &ptr->parsing, ptr);
        }
        ptr = ptr->next;
    }
}

void check_client_write_file(client_t **list_client, fd_set *write_fds)
{
    client_t *ptr = *list_client;
    client_t *temp = NULL;
    while(ptr != NULL) {

        if (FD_ISSET(ptr->fd, write_fds) && ptr->msg != NULL) {
            send_message_to_client(ptr->fd, ptr->msg->message, ptr->msg->code);
            pop_message(&ptr->msg);
        }
        if (ptr->state == DISCONNECT) {
            temp = ptr->next;
            close(ptr->fd);
            search_and_destroy(list_client, ptr->fd);
            ptr = temp;
            continue;
        }
        ptr = ptr->next;
    }
}