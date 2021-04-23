/*
** EPITECH PROJECT, 2021
** myFtp
** File description:
** directory
*/

#include "../../includes/my_ftp.h"

void p_print_directory(char *args, client_t *client)
{
    if (client->state == LOGGED) {
        if (strcmp(client->cdir, client->parent_dir) == 0)
            add_message_to_list("/", "257", &client->msg);
        else {
            add_message_to_list(client->cdir, "257", &client->msg);
        }
    }
    else {
        add_message_to_list("Login with USER first.", "530", &client->msg);
    }
}

void p_change_directory(char *args, client_t *client)
{
    if (client->state == LOGGED ) {
        if (args != NULL) {
            DIR *dir;
            char *buffer = malloc((sizeof(char) * 1024));
            snprintf(buffer, strlen(args) + strlen(client->parent_dir)
            +2, "%s/%s\r\n",client->parent_dir, args);
            if ((dir = opendir(buffer)) != NULL) {
                client->cdir = strdup(buffer);
                add_message_to_list("CWD okay.", "200", &client->msg);
            }
            else    
                add_message_to_list("Failed to change directory.",
                "550", &client->msg);
            free(buffer);
        }
        else
            add_message_to_list("Failed to change directory.",
        "550", &client->msg);
    }
    else
        add_message_to_list("Login with USER first.", "503", &client->msg);
}

void p_change_to_parent(char *args, client_t *client)
{
    if (client->state == LOGGED ) {
        client->cdir = client->parent_dir;
        add_message_to_list("CDUP okay.", "200", &client->msg);
    }
    else {
    add_message_to_list("Login with USER first.", "503", &client->msg);
    }
}

void p_delete_file(char *args, client_t *client)
{
    if (client->state == LOGGED && args != NULL) {
        int del;
        char *buffer = malloc((sizeof(char) * 1024));
        snprintf(buffer, strlen(args) + strlen(client->cdir)
            +2, "%s/%s\r\n",client->cdir, args);
        del = remove(buffer);
        if (del == 0)
            add_message_to_list("File deleted.", "250", &client->msg);
        else
            add_message_to_list("File not deleted.", "500", &client->msg);
        free(buffer);
    }
    else {
    add_message_to_list("Login with USER first.", "503", &client->msg);
    }
}