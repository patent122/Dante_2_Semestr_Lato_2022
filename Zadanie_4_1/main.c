#include <stdio.h>
#include <stdlib.h>
#include "tested_declarations.h"
#include "rdebug.h"

int main()
{
    int *input =  NULL;
    input = (int*)malloc(100 * sizeof(int));
    if(input == NULL)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    for (int i = 0; i < 100; ++i)
    {
        *(input + i) = i;
    }
    for (int i = 0; i < 100; ++i)
    {
        printf("%d ", *input+i);
    }

    free(input);

    return 0;
}
