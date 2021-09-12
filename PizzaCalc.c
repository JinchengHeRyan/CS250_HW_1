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
    for (int i = 0; i < 5; i++)
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
    char name[64];
    float diameter;
    float cost;
    float pizza_per_dolloar;
};

void copy_name(char *copied_in, char *copy_origin)
{
    int len = strlen(copy_origin);
    for (int i = 0; i < len; i++)
    {
        copied_in[i] = copy_origin[i];
    }
    copied_in[len] = 0;
}

void sortPizzaList(struct Pizza *pizza_list, int pizza_count)
{
    // Start sorting the pizza list
    float maxPPD;
    int maxIndex;

    for (int i = 0; i < pizza_count - 1; i++)
    {
        maxPPD = pizza_list[i].pizza_per_dolloar;
        maxIndex = i;

        for (int j = i + 1; j < pizza_count; j++)
        {
            if (pizza_list[j].pizza_per_dolloar > maxPPD)
            {
                maxPPD = pizza_list[j].pizza_per_dolloar;
                maxIndex = j;
            }
            else if (pizza_list[j].pizza_per_dolloar == maxPPD)
            {
                int min;
                if (strlen(pizza_list[j].name) < strlen(pizza_list[maxIndex].name))
                {
                    min = strlen(pizza_list[j].name);
                }
                else
                {
                    min = strlen(pizza_list[maxIndex].name);
                }
                for (int t = 0; t < min; t++)
                {
                    if (pizza_list[maxIndex].name[t] > pizza_list[j].name[t])
                    {
                        maxPPD = pizza_list[j].pizza_per_dolloar;
                        maxIndex = j;
                        break;
                    }
                    if (pizza_list[maxIndex].name[t] < pizza_list[j].name[t])
                    {
                        break;
                    }
                }
            }
        }
        struct Pizza temp_pointer = pizza_list[i];
        pizza_list[i] = pizza_list[maxIndex];
        pizza_list[maxIndex] = temp_pointer;
    }
}

int pizza_count = 0;

int main(int argc, char *argv[])
{
    // Check input parameters
    if (argc == 1)
    {
        printf("PIZZA FILE IS EMPTY\n");
    }

    if (argc == 2)
    {
        FILE *input_file = fopen(argv[1], "r");
        char arr[64];

        int pizza_list_length = 10;
        struct Pizza *pizza_list = (struct Pizza *)malloc(sizeof(struct Pizza) * pizza_list_length);

        // Read data into memory
        while (1)
        {
            if (fscanf(input_file, "%s", arr) != EOF)
            {
                if (!isDone(arr, strlen(arr)))
                {
                    // Determine whether the size of pizza list is enough
                    if (pizza_count >= pizza_list_length)
                    {
                        pizza_list = (struct Pizza *)realloc(pizza_list, 2 * pizza_list_length * sizeof(struct Pizza));
                        pizza_list_length = 2 * pizza_list_length;
                    }

                    // Put into name
                    copy_name(pizza_list[pizza_count].name, arr);

                    // Put into diameter value
                    fscanf(input_file, "%s", arr);
                    float diameter = atof(arr);
                    pizza_list[pizza_count].diameter = diameter;

                    // Put into cost value
                    fscanf(input_file, "%s", arr);
                    float cost = atof(arr);
                    pizza_list[pizza_count].cost = cost;
                    pizza_count++;
                }
                else
                {
                    break;
                }
            }
            else
            {
                printf("PIZZA FILE IS EMPTY\n");
                fclose(input_file);
                free(pizza_list);
                return EXIT_SUCCESS;
            }
        }
        fclose(input_file);

        // Begin processing the calculation
        for (int i = 0; i < pizza_count; i++)
        {
            if (pizza_list[i].cost == 0.0)
            {
                pizza_list[i].pizza_per_dolloar = 0;
            }
            else
            {
                pizza_list[i].pizza_per_dolloar = PI * pizza_list[i].diameter * pizza_list[i].diameter / 4 / pizza_list[i].cost;
            }
        }

        sortPizzaList(pizza_list, pizza_count);

        // Show the original information
        // printf("All Pizza Count = %d\n", pizza_count);
        for (int i = 0; i < pizza_count; i++)
        {
            // printf("The name is: %s\n", pizza_list[i].name);
            // printf("The diameter is: %f\n", pizza_list[i].diameter);
            // printf("The cost is: %f\n", pizza_list[i].cost);
            // printf("The pizza_per_dollar is: %f\n", pizza_list[i].pizza_per_dolloar);
            printf("%s %f\n", pizza_list[i].name, pizza_list[i].pizza_per_dolloar);
        }

        free(pizza_list);
    }
    return EXIT_SUCCESS;
}
