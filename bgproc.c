#include "alldefinitions.h"
#include <unistd.h>

void bgproc(char** args, int inredir,char* infile)
// void bgproc(char** args)
{
    int forkid=fork();
    if(forkid==-1)
    {
        printf("Error in forking child\n");
        return;
    }
    else if(forkid==0)
    {
        setpgid(0, 0);
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
            printf("Error in executing the command\n");
            // perror("Error");
        exit(0);
    }
    else
    {
        // for(int i=0;i<MAX_SIZE;i++)
        // {
        //     if(processarray[i].pid==-1)
        //     {
        //         processarray[i].pid=forkid;
        //         // printf("%d copied\n",processarray[i].pid);
        //         strcpy(processarray[i].name,args[0]);
        //         break;
        //     }
        // }
        processarray[bgend].pid=forkid;
        strcpy(processarray[bgend].name,args[0]);
        bgend++;
        printf("%d\n",forkid);
        return;
    }
}