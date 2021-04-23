/*
** EPITECH PROJECT, 2021
** myFtp
** File description:
** function_pointeur_second
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
            else {
                add_message_to_list("Failed to change directory.",
                "550", &client->msg);
            }
            free(buffer);
        }
    }
    else {
        add_message_to_list("Login with USER first.", "503", &client->msg);
    }
}

void p_noop(char *args, client_t *client)
{
    if (client->state == LOGGED) {
        add_message_to_list("NOOP ok.", "200", &client->msg);
    }
    else {
        add_message_to_list("Login with USER first.", "503", &client->msg);
    }
}

void p_help(char *args, client_t *client)
{
    if (client->state == LOGGED) {
        add_message_to_list("Help ok.", "214", &client->msg);
    }
    else {
        add_message_to_list("Login with USER first.", "503", &client->msg);
    }
}