/*
** EPITECH PROJECT, 2021
** myFtp
** File description:
** free_my_homies
*/

#include "../includes/my_ftp.h"

void free_my_client(client_t *client)
{
    message_t *msg = client->msg;
    parse_t *parse = client->parsing;

    free(client->CMD);
    free(client->cdir);
    while(msg != NULL) {
        free_my_message(msg);
        msg = msg->next;
    }
    while(parse != NULL) {
        free_my_parse(parse);
        parse = parse->next;
    }
    free(client);
}

void free_my_message(message_t *message)
{
    free(message);
}

void free_my_parse(parse_t *parse)
{
    free(parse->commande);
    free(parse->args);
    free(parse);
}