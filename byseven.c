#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    if (argc > 0)
    {
        int N = atoi(argv[1]);
        for (int i = 0; i < N; i++)
        {
            printf("%d\n", 7 * (i + 1));
        }
    }
    return EXIT_SUCCESS;
}