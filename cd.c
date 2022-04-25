#include "alldefinitions.h"

// int cd(char* startdir,char* prevdir)
int cd()
{
    char* path=strtok(NULL," \t\n");
    if(path== NULL)
    {
        path="~";
    }
    char* test=strtok(NULL," \t\n");
    if(test!=NULL)
    {
        printf("Error: cd can have only one argument\n");
        return 0;
    }
    char changedir[3*MAX_SIZE];
    // printf("entered %s\n",path);
    if(path[0]=='~')
    {
        if(strlen(path)==1)
        {
            strcpy(changedir,startdir);
        }
        else
        {
            char godir[MAX_SIZE];
            strcpy(godir,startdir);
            strcat(godir,"/");
            strcat(godir,path+1);
            // printf("going to:%s\n",godir);
            strcpy(changedir,godir);
        }
    }
    // else if(strcmp(path,"-")==0)
    else if(path[0]=='-')
    {
        // printf("prev dir time %s\n",prevdir);
        strcpy(changedir,prevdir);
    }
    else
    {
        strcpy(changedir,path);
    }
    // strcat(changedir,"/\0");
    // printf("searching %s\n",changedir);
    int err=chdir(changedir);
    if(err==-1)
    {
        printf("No such directory is present\n");
        return 0;
    }
    else 
    {
        return 1;
    }
}