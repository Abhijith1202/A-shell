#include "alldefinitions.h"

int notinbgq(int thepid)
{
    for(int i=0;i<bgend;i++)
    {
        if(processarray[i].pid==thepid)
            return 0;
    }
    return 1;
}

void fg(char* job)
{
    int jobno=atoi(job);
    // printf("jobno: %d\n",jobno);
    if(jobno > bgend || jobno==0 || processarray[jobno-1].pid==-1)
    {
        printf("Invalid job number: %d\n",jobno);
        return;
    }
    int thepid=processarray[jobno-1].pid;
    FGPID=thepid;
    strcpy(FGPROCNAME,processarray[jobno-1].name);
    shiftjobs(jobno-1);
    signal(SIGTTIN,SIG_IGN);
    signal(SIGTTOU, SIG_IGN); 
    tcsetpgrp(STDIN_FILENO, thepid);
    // processarray[jobno-1].pid=-1;
    kill(thepid,SIGCONT);
    int stat;
    waitpid(thepid,&stat,WUNTRACED);
    tcsetpgrp(STDIN_FILENO, getpgid(0)); 
    signal(SIGTTIN, SIG_DFL); 
    signal(SIGTTOU, SIG_DFL);
    if(WIFSTOPPED(stat))
	{
        if(notinbgq(thepid))
		{
            printf("\n%s with pid %d stopped and sent to bg\n", FGPROCNAME, thepid);
            // processarray[jobno-1].pid=FGPID;
            processarray[bgend].pid=thepid;
            strcpy(processarray[bgend].name,FGPROCNAME);
            bgend++;
        }
    }
    return;
}