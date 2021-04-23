/*
** EPITECH PROJECT, 2021
** myFtp
** File description: gestion du parsing
** parsgin_gesture
*/

#include "../includes/my_ftp.h"

void parsing_fd_receive(char *cmd, parse_t **parsing, client_t *client) {
    char *copy_cmd;
    int i = -1;
    parse_t *ptr = malloc(sizeof(parse_t));
    ptr->args = malloc(sizeof(char)* 1024);
    ptr->commande = malloc(sizeof(char)* 1024);
    ptr->next = NULL;
    copy_cmd = strdup(cmd);
    ptr->commande = strtok(copy_cmd, " \r\n \0");
    ptr->args = strtok(NULL, "\r\n \0");
    i = check_flag(ptr->commande, client);
    if (i != -1) {
        tab_function[i].callback(ptr->args, client);
    }

}
