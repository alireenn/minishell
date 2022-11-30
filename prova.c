#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void ft_hand(int sig)
{
    printf("%d\n", sig);
    exit (5);
}



int main()
{
    signal(SIGINT, ft_hand);
    while (1)
    {
        continue ;
    }
}