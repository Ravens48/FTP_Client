/*
** EPITECH PROJECT, 2021
** myFtp
** File description:
** main
*/

#include "../includes/my_ftp.h"

void helper()
{
    printf("USAGE: ./myftp port path\n");
    printf("\t port is the port number on wich the server socket listen\n");
    printf("\t path is the path to the home directory for the Anonymous user\n");
}

int error_handle(int ac, char **av)
{
    DIR *dir;
    if (ac < 3) {
        printf("Need arguments refere to -help\n");
        return (84);
    }
    else if (ac == 2 && strcmp(av[1], "-help") == 0) {
        helper();
        return 84;
    }
    else if (ac >= 2) {
        for (int i = 0; av[1][i] != '\0'; i++) {
            if (av[1][i] < '0' || av[1][i] >'9') {
                return 84;
            }
        }
        if (av[2] != NULL) {
            if ((dir = opendir(av[2])) == NULL)
                return 84;
            closedir(dir);
        }
    }
}

int main(int ac, char **av)
{
    setbuf(stdout, NULL);
    int fd;
    if (error_handle(ac, av) == 84)
        return 84;
    fd = starting_serv(atoi(av[1]), INADDR_ANY);
    running_serv(fd, av[2]);
    return (0);
}
