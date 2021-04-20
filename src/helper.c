/*
** EPITECH PROJECT, 2021
** myFtp
** File description:
** helper
*/

#include "../includes/my_ftp.h"

//remplacer message et code par la liste chainee
void send_message_to_client(int fd, char *message, char* code)
{
    char *buffer = malloc(sizeof(char) * 1024);
    
    snprintf(buffer, strlen(message) + strlen(code) + 1, "%s %s\r\n", code, message);

    write(fd, buffer, strlen(buffer+1));
    free(buffer);
    return;
}


void add_message_to_list(char * message, char* code, message_t **list_msg)
{
    message_t *list_m = malloc(sizeof(message_t));
    message_t *ptr = *list_msg;

    printf("ADDING A MESSAGE\n");
    list_m->message = message;
    list_m->code = code;
    list_m->next = NULL;

    if (ptr == NULL) {
        *list_msg = list_m;
        return;
    }
    while(ptr->next != NULL) {
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

void *pop_client(client_t **list_client)
{
    void *node = NULL;
    client_t *ptr = *list_client;

    if (ptr == NULL) {
        free(ptr->CMD);
        free(ptr->cdir);
        free(ptr); 
        return NULL;
    }
    if (ptr->next == NULL) {
        free(ptr->CMD);
        free(ptr->cdir);
        free(ptr);
        *list_client = NULL;
        return node;
    }
    while (ptr->next->next != NULL)
        ptr = ptr->next;
    free(ptr->next);
    ptr->next = NULL;
}

/* Checks whether the value x is present in linked list */
void search_and_destroy(client_t **list_client, int client_fd)
{
    client_t *ptr = *list_client;
    client_t *s_ptr = NULL;
    while (ptr != NULL)
    {
        s_ptr = ptr->next;
        if (ptr->fd == client_fd)
            pop_client(&ptr);
        ptr = s_ptr;
    }
}
