#include "alldefinitions.h"
#include "library.h"
#include <stdlib.h>
#include <string.h>

// process processarray[MAX_SIZE];
// char startdir[MAX_SIZE];
// char prevdir[MAX_SIZE];
// int bgprocdone=0;

void shiftjobs(int pos)
{
    if(bgend==0 || pos==bgend)
    {
        processarray[0].pid=-1;
        strcpy(processarray[0].name,"\0");
        return;
    }
    for(int i=pos;i<bgend;i++)
    {
        processarray[i].pid=processarray[i+1].pid;
        strcpy(processarray[i].name,processarray[i+1].name);
    }
    bgend--;
    // printf("After shiftjobs, bgend is now %d\n",bgend);
}

void checkbgprocess()
{
    int waitstatus;
    int finchild=waitpid(-1,&waitstatus,WNOHANG);
    // printf("funcciton call successful for %d\n",finchild);
    if(finchild > 0)
    {
        for(int i=0;i<=bgend;i++)
        {
            if(processarray[i].pid==finchild)
            {
                if(WIFEXITED(waitstatus))
                {
                    printf("\n%s with pid %d exited normally\n",processarray[i].name,finchild);
                }
                else
                {
                    printf("\n%s with pid %d exited abnormally\n",processarray[i].name,finchild);
                }
                // processarray[i].pid=-1;
                shiftjobs(i);
                // printf("prompt should be printed below\n");
                display();
                fflush(stdout);
                // fflush(stdin);
                // bgprocdone=1;
                // printf("bgprocdone set to 1: %d\n",bgprocdone);
                break;
            }
        }
    }
}

void ctrlc()
{
    int pid=getpid();
    if(pid != SHELLPID)
        return;
    
    if(FGPID!=-1)
    {
        // printf("\n");
        kill(FGPID,SIGINT);
        // bgprocdone=1;
        // printf("\n");
    }
    signal(SIGINT,ctrlc);
}

void movetobg(int pid, char* procname)
{
    if(bgend>=MAX_SIZE)
    {
        printf("Background queue full\n");
        return;
    }
    processarray[bgend].pid=pid;
    strcpy(processarray[bgend].name,procname);
    bgend++;
    // printf("current bgend=%d\n",bgend);
}

void ctrlz(int sig)
{
    int pid=getpid();
    if(pid != SHELLPID)
        return;
    // if(FGPID==-1)
    // {
    //     display();
    //     fflush(stdout);
    // }
    if(FGPID!=-1)
    {
        // printf("\n");
        printf("\nSending %s with pid %d to bg\n",FGPROCNAME,FGPID);
        movetobg(FGPID,FGPROCNAME);
        // kill(FGPID,SIGTTIN);
        kill(FGPID,SIGTSTP);
        // bgprocdone=1;

        // addtobg(FGPID,FGPROCNAME);
        // display();
        // fflush(stdout);
        
        // printf("\n");
    }
    
    signal(SIGTSTP,ctrlz);
    // if(pid==SHELLPID)
    // {
    //     display();
    //     fflush(stdout);
    // }
    return;
}

int main()
{
    // char startdir[MAX_SIZE];
    SHELLPID=getpid();
    getcwd(startdir,MAX_SIZE);
    char dummyprevdir[MAX_SIZE];
    getcwd(prevdir,MAX_SIZE);
    // char history[20][MAX_SIZE];
    for(int i=0;i<20;i++)
    {
        strcpy(history[i],"\0");
    }
    char* mainline;
    // char* commands[MAX_SIZE];
    // char outfile[MAX_SIZE];
    // char infile[MAX_SIZE];
    size_t size=MAX_SIZE;
    size_t read;
    // char* realcommand;
    char filepath[MAX_SIZE];
    int stored=0;
    strcpy(filepath,startdir);
    strcat(filepath,"/hist.txt");
    // printf("opening file\n");
    FILE *f=fopen(filepath,"rb");
    // printf("file opened\n");
    if(f==NULL)
    {
        for(int i=0;i<20;i++)
        {
            strcpy(history[i],"\0");
        }
    }
    else //wip
    {
        fread(&history,sizeof(history),1,f);

        for(int i=0;i<20;i++)
        {
            if(strcmp(history[i],"\0")!=0)
            {
                stored++;
            }
        }
        fclose(f);
    }
    
    for (int i=0;i<MAX_SIZE;i++)
    {
        processarray[i].pid=-1;
    }
    int ogstdin,ogstdout;
    dup2(0,ogstdin);
    dup2(1,ogstdout);
    signal(SIGCHLD,checkbgprocess);
    signal(SIGINT,ctrlc);
    signal(SIGTSTP,ctrlz);
    // signal(SIGTTIN,SIG_DFL);
    // signal(SIGTTOU,SIG_DFL);
    while(1)
    {
        FGPID=-1;
        dup2(ogstdin,0);
        dup2(ogstdout,1);
        // display(startdir);
        display();
        fflush(stdout);
        // read=getline(&commands[commcount],&size,stdin);
        read= getline(&mainline,&size,stdin);
        // commands[commcount][strlen(commands[commcount])-1]='\0';
        if(read==-1|| read==1)
        {
            if(read==-1)
            {
                printf("Logged out without saving history\n");
                exit(0);
            }
            continue;
        }
        char* tokenc;
        char* commands[MAX_SIZE];
        int donecommands=0;
        tokenc=strtok(mainline,";\n");
        while(tokenc!=NULL)
        {
            commands[donecommands]=(char*)malloc(strlen(tokenc));
            strcpy(commands[donecommands],tokenc);
            // printf("%d: %s\n",donecommands,commands[donecommands]);
            donecommands++;
            tokenc=strtok(NULL,";\n");
        }
        // int ogstdin,ogstdout;
        // dup2(0,ogstdin);
        // dup2(1,ogstdout);
        // donecommands+=comno;
        for(int i=0;i<donecommands;i++)
        {
            int qflag=executecom(commands[i],&stored,0);
            if(qflag==1)
            {
                char filepath[MAX_SIZE];
                strcpy(filepath,startdir);
                strcat(filepath,"/hist.txt");
                FILE *f=fopen(filepath,"wb");
                fwrite(history,sizeof(history),1,f);
                // fwrite(history,(20*2000),1,f);
                fclose(f);
                exit(0);
            }
            fflush(stdin);
            
            dup2(ogstdin,0);
            dup2(ogstdout,1);
        }
    }
    return 0;
}