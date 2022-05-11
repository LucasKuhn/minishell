#include<stdio.h>
#include<signal.h>
#include <unistd.h>
#include <stdlib.h>

void handle_sigint(int sig)
{
    printf("Caught signal %d\n", sig);
}

int main()
{
    int i;

	i = 0;
    while (i < 3)
    {
        printf("hello world\n");
        sleep(1);
		i++;
    }
    exit(42);
}

/* int main()
{
    //signal(SIGINT, handle_sigint);
    while (1)
    {
        printf("hello world\n");
        sleep(1);
    }
    return 0;
} */
