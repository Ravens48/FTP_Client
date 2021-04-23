/*
** EPITECH PROJECT, 2021
** myFtp
** File description:
** function_pointeur_second
*/

#include "../../includes/my_ftp.h"

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