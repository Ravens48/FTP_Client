/*
** EPITECH PROJECT, 2021
** myFtp
** File description:
** function_pointer
*/

#include "../../includes/my_ftp.h"

int check_flag(char *flag, client_t *client)
{
    if (flag == NULL) {
        add_message_to_list("You send only space.", "500", &client->msg);
        return -1;
    }
    else if (flag != NULL) {
        for (int i = 0; tab_function[i].flag != "\0"; i++) {
            if ((strcmp(flag, tab_function[i].flag)) == 0) {
                return (i);
            }
        }
    }
    add_message_to_list("Unknow command.", "500", &client->msg);
    return (-1);
}

void p_quit(char *args, client_t *client)
{
    client->state = DISCONNECT;
    add_message_to_list("Service closing control connection.",
    "221", &client->msg);
}

void p_user_identify(char *args, client_t *client)
{
    if (client->state == UNKNOW && args != NULL) {
        client->state = ONLY_USER;
        if (strcmp(args,"Anonymous") == 0)
            client->valid_user = 1;
        add_message_to_list("User name okay, need password.",
        "331", &client->msg);
    }
    else if (client->state == LOGGED && args != NULL)
        add_message_to_list("User logged in, proceed.", "230", &client->msg);
    else {
        client->state = UNKNOW;
        add_message_to_list("Permission denied.", "530", &client->msg);
    }
}

void p_user_connect(char *args, client_t *client)
{
    if (client->state == ONLY_USER && client->valid_user == 1) {
        client->state = LOGGED;
        add_message_to_list("User logged in, proceed.", "230", &client->msg);
    }
    else if (client->state == UNKNOW)  {
        add_message_to_list("Need account for login.", "332", &client->msg);
    }
    else {
        client->state = UNKNOW;
        add_message_to_list("Permission denied.", "530", &client->msg);
    }
}