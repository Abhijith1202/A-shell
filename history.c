#include "alldefinitions.h"


int savehistory(int commcount,char command[MAX_SIZE])
{
    strcat(command,"\n");
    if(strcmp(history[19],command)==0)
    {
        return commcount;
    }
    if(commcount>=20)
    {
        for(int i=0;i<19;i++)
        {
            strcpy(history[i],history[i+1]);
        }
        strcpy(history[19],command);
        // strcat(history[19],"\n");
    }
    else
    {
        for(int i=20-commcount-1;i<19;i++)
        {
            strcpy(history[i],history[i+1]);
        }
        strcpy(history[19],command);
        // strcat(history[19],"\n");
    }
    commcount++;
    return commcount;
}

void displayhistory(int stored)
{
    int dispno=10;
    char* token=strtok(NULL," \t\n");
    if(token!=NULL)
    {
        dispno=0;
        int base=1;
        int l=strlen(token);
        for(int i=l-1;i>=0;i--)
        {
            dispno=dispno+(base*(token[i]-'0'));
            base*=10;
        }
        if(dispno>20)
        {
            printf("History restricted to printing maximum of 20 commands:\n");
            dispno=20;
        }
    }
    if(dispno>stored)
    {
        // printf("Only %d commands have been performed:\n",stored);
        dispno=stored;
    }
    
    for(int i=20-dispno;i<20;i++)
    {
        printf("%s",history[i]);
    }
}




