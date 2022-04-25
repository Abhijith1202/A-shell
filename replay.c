#include "alldefinitions.h"

//executecom(char* commands,int* stored)

void replay(int* stored)
{
    // char command[MAX_SIZE];
    char* command=(char*)malloc(MAX_SIZE);
    int interval,period;
    int iflag=1,pflag=1,ccount=0,icount=0,pcount=0;
    char* token=strtok(NULL," \t\n");
    while(token!=NULL)
    {
        if(strcmp(token,"-command")==0)
        {
            ccount++;
            iflag=1;
            pflag=1;
            token=strtok(NULL," \t\n");
        }
        else if(strcmp(token,"-interval")==0)
        {
            iflag=0;
            icount++;
            token=strtok(NULL," \t\n");
            if(token==NULL)
            {
                printf("No interval provided. format: replay -command <command> -interval <interval> -period <period>");
                return;
            }
            interval=atoi(token);
            if(interval==0)
            {
                printf("interval should be a positive integer\n");
                return;
            }
            token=strtok(NULL," \t\n");
        }
        else if(strcmp(token,"-period")==0)
        {
            pflag=0;
            pcount++;
            token=strtok(NULL," \t\n");
            if(token==NULL)
            {
                printf("No period provided. format: replay -command <command> -interval <interval> -period <period>");
                return;
            }
            period=atoi(token);
            if(period==0)
            {
                printf("period should be a positive integer\n");
                return;
            }
            token=strtok(NULL," \t\n");
        }
        else if(token[0]=='-')
        {
            printf("invalid flag: %s\nvalid flags are '-command', '-interval' and '-period'\n",token);
            return;
        }
        else if(ccount && iflag && pflag)
        {
            strcat(command,token);
            strcat(command," ");
            token=strtok(NULL," \t\n");
        }
        else
        {
            printf("invalid entry. format: replay -command <command> -interval <interval> -period <period>\n");
            return;
        }
    }
    if(ccount!=1 || icount!=1 || pcount!=1)
    {
        printf("invalid entry. format: replay -command <command> -interval <interval> -period <period>\n");
        return;
    }
    // if(cflag==0)
    // {
    //     printf("invalid entry. format: replay -command <command> -interval <interval> -period <period>\n");
    //     return;
    // }
    // printf("interval: %d, period: %d, command: %s",interval,period,command);
    if(strcmp(command,"")==0)
    {
        printf("Enter a valid command after the command flag\n");
        return;
    }
    while(period>0)
    {
        sleep(interval);
        period-=interval;
        executecom(command,stored,1);
    }
    free(command);
}