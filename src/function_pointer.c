/*
** EPITECH PROJECT, 2021
** myFtp
** File description:
** function_pointer
*/

#include "../includes/my_ftp.h"

int check_flag(char *flag)
{
    if (flag != NULL) {
        for (int i = 0; tab_function[i].flag != "\0"; i++) {
            printf("flag ? : %s\n", tab_function[i].flag);
            printf("flag ? : %s\n", flag);
            if ((strcmp(flag, tab_function[i].flag)) == 0) {
                return (i);
            }
        }
    }
    return (-1);
}


void p_quit(char *args, client_t *client)
{
    client->state = DISCONNECT;
    printf("STATE in pquit %d\n", client->state);
    add_message_to_list("Service closing control connection.", "221", &client->msg);
}

void p_user_identify(char *args, client_t *client)
{
    printf("ARRRRGS :%s\n status: %d\n", args, client->state);
    //cas ou user unknow ou pass pas encore renseigne apres user ok
    if (client->state == UNKNOW && args != NULL) {
        client->state = ONLY_USER;
        if (strcmp(args,"Anonymous") == 0)
            client->valid_user = 1;
        add_message_to_list("User name okay, need password.", "331", &client->msg);
    }
    else {
        add_message_to_list("Permission denied.", "530", &client->msg);
    }
}

void p_user_connect(char *args, client_t *client)
{
    //cas ou user unknow ou pass pas encore renseigne apres user ok
    if (client->state == ONLY_USER && client->valid_user == 1) {
        client->state = LOGGED;
        add_message_to_list("User logged in, proceed.", "230", &client->msg);
    }
    else if (client->state == UNKNOW)  {
        add_message_to_list("Need account for login.", "332", &client->msg);
    }
    else {
        add_message_to_list("Permission denied.", "530", &client->msg);
    }
}

// void p_print_directory(char *args, client_t *client)
// {
//     if (client->state == LOGGED) {
//         add_message_to_list("User name okay, need password.", "331", &client->msg);
//     }
// }

void p_noop(char *args, client_t *client)
{
    // 200 NOOP ok.
    if (client->state == LOGGED) {
        add_message_to_list("NOOP ok.", "200", &client->msg);
    }
    else {
        add_message_to_list("Login with USER first.", "503", &client->msg);
    }
}