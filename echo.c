#include "alldefinitions.h"

void echocall()
{
    //printf("%s ",string);
    // char *token = string;
    char* token=strtok(NULL," \t\n");
    //printf("%s\n",token);
    while(token!=NULL)
    {
        // for(int i=0;token[i]!='\0';i++)
        //     printf("%c",token[i]);
        if(strcmp(token,">")==0)
            break;
        printf("%s ",token);
        // printf(" ");
        
        token=strtok(NULL," \t\n");
    }
    printf("\n");
}