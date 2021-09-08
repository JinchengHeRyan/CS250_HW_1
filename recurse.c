#include <stdio.h>
#include <stdlib.h>

int f(int N)
{
    if (N == 0)
    {
        return 2;
    }
    return 3 * (N - 1) + f(N - 1) + 1;
}

int main(int argc, const char *argv[])
{
    if (argc > 0)
    {
        int N = atoi(argv[1]);
        printf("%d\n", f(N));
    }
    return EXIT_SUCCESS;
}