#include "alldefinitions.h"

void bg(char* job)
{
    int jobno=atoi(job);
    if(jobno>MAX_SIZE || processarray[jobno-1].pid == -1)
    {
        printf("Invalid job number: %d\n",jobno);
    }
    else
        kill(processarray[jobno-1].pid,SIGCONT);
}