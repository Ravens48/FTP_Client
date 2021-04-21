/*
** EPITECH PROJECT, 2021
** myFtp
** File description:
** function_pointer
*/

#include "../includes/my_ftp.h"

int check_flag(char *flag)
{
    for (int i = 0; tab_function[i].flag != "\0"; i++) {
        printf("flag ? : %s\n", tab_function[i].flag);
        printf("flag ? : %s\n", flag);
        if ((strcmp(flag, tab_function[i].flag)) == 0) {
            return (i);
        }
    }
    return (-1);
}


void p_quit(char *args, client_t *client)
{
    client->state = DISCONNECT;
}