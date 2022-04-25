#include "alldefinitions.h"
#include <unistd.h>

void pinfo()
{
    char pid[MAX_SIZE];
    char* token=strtok(NULL," \t\n");
    if(token == NULL)
    {
        int shellpid=getppid();
        sprintf(pid,"%d",shellpid);
    }
    else
    {
        strcpy(pid,token);
    }
    char procdest[MAX_SIZE]="/proc/";
    strcat(procdest,pid);
    char procstat[MAX_SIZE];
    strcpy(procstat,procdest);
    strcat(procstat,"/stat");
    char procmem[MAX_SIZE];
    strcpy(procmem,procdest);
    strcat(procmem,"/statm");
    // char procexe[MAX_SIZE];
    char* procexe=(char*)malloc(MAX_SIZE);
    strcpy(procexe,procdest);
    strcat(procexe,"/exe");

    FILE* procfile=fopen(procstat,"r");
    if(procfile==NULL)
    {
        printf("Error, no process with pid= %s exists\n",pid);
        return;
    }
    else
    {
        char dumm1[MAX_SIZE], dumm2[MAX_SIZE], status[MAX_SIZE];
        int parent,group;
        fscanf(procfile,"%s %s %s %d %d",dumm1,dumm2,status,&parent,&group);
        printf("pid -- %s\n",pid);
        int ownid=getppid();
        // printf("parent: group= %d : %d\n",parent,group);
        if(ownid==group)
        {
            strcat(status,"+");
        }
        printf("Process Status -- %s\n",status);
    }

    procfile=fopen(procmem,"r");
    char memory[MAX_SIZE];
    fscanf(procfile,"%s",memory);
    printf("memory -- %s {Virtual Memory}\n",memory);

    // char execpath[MAX_SIZE];
    char* execpath = (char*)malloc(MAX_SIZE);
    ssize_t linksize;
    linksize=readlink(procexe,execpath,MAX_SIZE);
    if(linksize<0)
    {
        printf("Error in finding the executable\n");
        return;
    }
    int l1=strlen(startdir);
    int l2=strlen(execpath);
    execpath[l2]='\0';
    // printf("%d %ld %s\n",l2,linksize,execpath);
    int i=0;
    for(i=0;i<l1 && i<l2; i++)
    {
        if(startdir[i]!=execpath[i])
            break;
    }

    if (i==l1)
    {
        if(l1==l2 || execpath[l1]=='/')
        {
            execpath[0]='~';
            int j=l1;
            for(j=l1;j<l2;j++)
            {
                execpath[j-l1+1]=execpath[j];
            }
            execpath[l2-l1+1]='\0';
        }
    }
    printf("Executable Path -- %s\n",execpath);
    free(execpath);
    free(procexe);
    return;
}