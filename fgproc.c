#include "alldefinitions.h"

void fgproc(char **args,int inredir,char* infile)
// void fgproc(char** args)
{
    int forkid=fork();
    FGPID=forkid;
    strcpy(FGPROCNAME,args[0]);
    if(forkid==-1)
    {
        printf("Error in forking child\n");
        return;
    }
    else if(forkid==0)
    {
        if(inredir>0)
        {
            int infd=open(infile,O_RDONLY);
            if(infd<0)
            {
                printf("No file with filename: %s found\n",infile);
                // continue;
                exit(0);
            }
            else
            {
                // printf("file opened: %s\n",infile);
                dup2(infd,STDIN_FILENO);
                close(infd);
            }
        }
        int try=execvp(args[0],args);
        if(try<0)
            {
                printf("Error in executing the command: ");
                for(int i=0;args[i]!=NULL;i++)
                {
                    printf("%s ",args[i]);
                }
                printf("\n");
                // return;
                exit(0);
            }
            // perror("Error");
        exit(0);
    }
    else
    {
        // FGPID=forkid;
        // strcpy(FGPROCNAME,args[0]);
        int stat;
        // printf("Printed\n");
        // wait(NULL);
        waitpid(forkid,&stat,WUNTRACED);
        return;
    }
}