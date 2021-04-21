/*
** EPITECH PROJECT, 2021
** myFtp
** File description: gestion du parsing
** parsgin_gesture
*/

#include "../includes/my_ftp.h"

void parsing_fd_receive(char *cmd, parse_t **parsing) {
    char *copy_cmd;
    parse_t *ptr = malloc(sizeof(parse_t));
    ptr->args = malloc(sizeof(char)* 1024);
    ptr->commande = malloc(sizeof(char)* 1024);
    ptr->next = NULL;
    copy_cmd = strdup(cmd);
    printf("cmd : %s\n", copy_cmd);
}
