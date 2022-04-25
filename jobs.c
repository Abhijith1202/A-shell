#include "alldefinitions.h"

static int compar(const void* a, const void* b)
{
    jobstruct* ja=(jobstruct*)a;
    jobstruct* jb=(jobstruct*)b;
    return strcmp(ja->jobname,jb->jobname);
}

void jobs(int runflag, int stopflag) //sorting to be implemented
{
    // int i=0;
    jobstruct* jobarray=(jobstruct*)malloc(bgend*sizeof(jobstruct));
    int jobcount=0;
    char status;
    for(int i=0;i<bgend;i++)
    {
        if(processarray[i].pid!=-1)
        {
            // printf("[%d] ",procno);
            char statfile[MAX_SIZE]="/proc/";
            char pidchar[MAX_SIZE];
            sprintf(pidchar,"%d",processarray[i].pid);
            strcat(statfile,pidchar);
            strcat(statfile,"/stat");
            FILE* stfile=fopen(statfile,"r");
            if(stfile)
            {
                fscanf(stfile,"%*d %*s %c",&status);
                // printf("[%d] %s %s [%d]\n",procno,(status== 'T' ? "Stopped" : "Running"),proc[i].name,proc[i].pid);
                if(status=='T' && stopflag)
                {
                    // printf("[%d] %s %s [%d]\n",i+1,"Stopped",processarray[i].name,processarray[i].pid);
                    jobarray[jobcount].jobnumber=i+1;
                    strcpy(jobarray[jobcount].jobname,processarray[i].name);
                    strcpy(jobarray[jobcount].status,"Stopped");
                    jobarray[jobcount].pid=processarray[i].pid;
                    jobcount++;
                    // procno++;
                }
                else if(status!='T' && runflag)
                {
                    // printf("[%d] %s %s [%d]\n",i+1,"Running",processarray[i].name,processarray[i].pid);
                    jobarray[jobcount].jobnumber=i+1;
                    strcpy(jobarray[jobcount].jobname,processarray[i].name);
                    strcpy(jobarray[jobcount].status,"Running");
                    jobarray[jobcount].pid=processarray[i].pid;
                    jobcount++;
                    // procno++;
                }
                fclose(stfile);
            }
            // else
            // {
            //     perror("Error:");
            // }
        }
    }
    if(jobcount==0)
        printf("No background processes\n");
    else
    {
        qsort(jobarray,jobcount,sizeof(jobstruct),compar);
        for(int i=0;i<jobcount;i++)
        {
            printf("[%d] %s %s [%d]\n",jobarray[i].jobnumber,jobarray[i].status,jobarray[i].jobname,jobarray[i].pid);
        }
    }
    free(jobarray);
    // if(procno==1)
    //     printf("No background processes\n");
}