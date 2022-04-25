#include "alldefinitions.h"


void repeat(int* stored)
{
    // char command[MAX_SIZE];
    char* command=(char*)malloc(MAX_SIZE);
    char* countstr=strtok(NULL," \t\n");
    // printf("%s\n",count);
    int count,forkid;
    sscanf(countstr,"%d",&count);
    // printf("%d\n",count);
    char* token=strtok(NULL," \t\n");
    while (token!=NULL)
    {
        strcat(command,token);
        strcat(command," ");
        token=strtok(NULL," \t\n");
    }
    for(int i=1;i<=count;i++)
        executecom(command,stored,1);
    free(command);
}

