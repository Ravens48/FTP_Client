/*
** EPITECH PROJECT, 2021
** myFtp
** File description:
** helper
*/

#include "../includes/my_ftp.h"

void send_message_to_client(int fd, char *message, char *code)
{
    char *buffer = malloc((sizeof(char) * 1024));

    snprintf(buffer, strlen(message) + strlen(code) 
    +4, "%s %s\r\n", code, message);

    write(fd, buffer, strlen(buffer));
    free(buffer);
    return;
}

void add_message_to_list(char *message, char *code, message_t **list_msg)
{
    message_t *list_m = malloc(sizeof(message_t));
    message_t *ptr = *list_msg;

    list_m->message = message;
    list_m->code = code;
    list_m->next = NULL;

    if (ptr == NULL) {
        *list_msg = list_m;
        return;
    }
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }
    ptr->next = list_m;
}

void *pop_message(message_t **list_msg)
{
    void *node = NULL;
    message_t *ptr = *list_msg;

    if (ptr == NULL)
        return NULL;
    if (ptr->next == NULL) {
        free(ptr);
        *list_msg = NULL;
        return node;
    }
    while (ptr->next->next != NULL)
        ptr = ptr->next;
    free(ptr->next);
    ptr->next = NULL;
}

void search_and_destroy(client_t **list_client, int client_fd)
{
    client_t *ptr = *list_client;
    client_t *s_ptr = NULL;
    while (ptr != NULL)
    {
        if (ptr->fd == client_fd) {
            if (s_ptr == NULL)
                *list_client = ptr->next;
            else {
                s_ptr->next = ptr->next;
            }
            free_my_client(ptr);
            return;
        }
        s_ptr = ptr;
        ptr = ptr->next;
    }
}
