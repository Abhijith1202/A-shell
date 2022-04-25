#include "alldefinitions.h"

void pwd()
{
    char current[MAX_SIZE]; 
    getcwd(current,MAX_SIZE);
    printf("%s\n",current);
}