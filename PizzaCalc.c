#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PI 3.14159265358979323846

int isDone(char *str, int len)
{
    char done_str[] = "DONE";
    if (len < 4)
    {
        return 1;
    }
    for (int i = 0; i < 4; i++)
    {
        if (str[i] != done_str[i])
        {
            return 0;
        }
    }
    return 1;
}

struct Pizza
{
    char name[60];
    float diameter;
    float cost;
};

void copy_name(char *copied_in, char *copy_origin)
{
    int len = strlen(copy_origin) - 1;
    for (int i = 0; i < len; i++)
    {
        copied_in[i] = copy_origin[i];
    }
    copied_in[len] = 0;
}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        FILE *input_file = fopen(argv[1], "r");
        char arr[60];

        int pizza_list_length = 10;
        int pizza_count = 0;
        struct Pizza *pizza_list = (struct Pizza *)malloc(sizeof(struct Pizza) * pizza_list_length);

        while (1)
        {
            if (fgets(arr, 60, input_file) != NULL)
            {
                printf("current line = %s\n", arr);
                if (!isDone(arr, 60))
                {
                    printf("current pizza count = %d\n", pizza_count);
                    // Determine whether the size of pizza list is enough
                    if (pizza_count >= pizza_list_length)
                    {
                        printf("size = %d\n", pizza_count);
                        struct Pizza *pizzalist = (struct Pizza *)realloc(pizza_list, 2 * pizza_list_length * sizeof(struct Pizza));
                        pizza_list_length = 2 * pizza_list_length;
                    }

                    // Put into name
                    copy_name(pizza_list[pizza_count].name, arr);

                    // Put into diameter value
                    fgets(arr, 60, input_file);
                    float diameter = atof(arr);
                    pizza_list[pizza_count].diameter = diameter;

                    // Put into cost value
                    fgets(arr, 60, input_file);
                    float cost = atof(arr);
                    pizza_list[pizza_count].cost = cost;
                    pizza_count++;
                }
                else
                {
                    break;
                }
            }
        }
        fclose(input_file);

        for (int i = 0; i < pizza_count; i++)
        {
            printf("The name is: %s\n", pizza_list[i].name);
            printf("The diameter is: %f\n", pizza_list[i].diameter);
            printf("The cost is: %f\n", pizza_list[i].cost);
        }
    }
    if (argc == 1)
    {
        printf("PIZZA FILE IS EMPTY\n");
    }
    return EXIT_SUCCESS;
}