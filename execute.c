#include "alldefinitions.h"

int checkpiping(char* command)
{
    for(int i=0;command[i]!='\0';i++)
    {
        if(command[i]=='|')
            return 1;
    }
    return 0;
}


char** pipedcommands(char* command)
{
    char* token=strtok(command,"|");
    char **pipedcomms=(char**)malloc(200*sizeof(char*));
    int i=0;
    while(token!=NULL)
    {
        pipedcomms[i++]=token;
        token=strtok(NULL,"|");
    }
    return pipedcomms;
}

void piped(char* commands,int* stored)
{
    char** pipedcomms=pipedcommands(commands);
    int pipearr[2], f=0;
    pid_t forkid;
    for(int i=0;pipedcomms[i]!=NULL;i++)
    {
        pipe(pipearr);
        forkid=fork();
        if(forkid<0)
        {
            printf("Fork error\n");
            return;
        }
        else if(forkid > 0)
        {
            wait(NULL);
            close(pipearr[1]);
            f=pipearr[0];
        }
        else if(forkid==0)
        {
            dup2(f,0);
            if(pipedcomms[i+1]!=NULL)
            {
                dup2(pipearr[1],1);
            }
            close(pipearr[0]);
            executecom(pipedcomms[i],stored,0);
            exit(0);
        }    
    }
}

void sig(int jobid, int signo)
{
    if(jobid>MAX_SIZE || processarray[jobid-1].pid==-1)
        printf("No job with job id: %d exists\n",jobid);
    else
    {
        printf("signal %d sent to process %s with pid %d\n",signo,processarray[jobid-1].name,processarray[jobid-1].pid);
        kill(processarray[jobid-1].pid,signo);
    }
}



int executecom(char* commands,int* stored,int repeatflag)
{
    char dummyprevdir[MAX_SIZE];
    int donecommands=0;
    // char* commands[MAX_SIZE];
    char outfile[MAX_SIZE];
    char infile[MAX_SIZE];
    size_t size=MAX_SIZE;
    size_t read;
    char* realcommand;
    if(repeatflag==0)
    {
        *stored=savehistory(*stored,commands);
        fflush(stdin);
    }
    char commandredir[MAX_SIZE];
    strcpy(commandredir,commands);
    if(checkpiping(commands))
    {
        // printf("checking piping\n");
        piped(commands,stored);
        return 0;
    }

    // check redir
    int outredir=outredircheck(commandredir,outfile);
    int inredir=inredircheck(commandredir,infile);
    // printf("redirections checked\n");
    if(outredir>0)
    {
        if(outredir==1)
        {
            int outfd=open(outfile, O_WRONLY|O_CREAT|O_TRUNC, 0644);
            dup2(outfd,STDOUT_FILENO);
            close(outfd);
        }
        else
        {
            int outfd=open(outfile, O_WRONLY|O_CREAT|O_APPEND, 0644);
            dup2(outfd,STDOUT_FILENO);
            close(outfd);
        }
    }
    char redirparsedcommand[MAX_SIZE];
    for(int j=0;commands[j]!='\0';j++)
    {
        if(commands[j] =='>' || commands[j] == '<' || commands[j]=='\n')
        {
            redirparsedcommand[j]='\0';
            break;
        }
        redirparsedcommand[j]=commands[j];
    }
    // printf("parsed wrt <> : %s\n",redirparsedcommand);
    // printf("Before strtok\n");
    // realcommand=strtok(commands," \t\n");
    realcommand=strtok(redirparsedcommand," \t\n");
    // printf("beginning strcmp for %s\n",realcommand);
    // printf("After strtok %s\n",realcommand);
    if(strcmp(realcommand,"clear")==0)
    {
        clear();
        return 0;
    }
    else if(strcmp(realcommand,"pwd")==0)
    {
        pwd();
        return 0;
    }
    else if(strcmp(realcommand,"echo")==0)
    {
        echocall();
        return 0;
    }
    else if(strcmp(realcommand,"cd")==0)
    {
        getcwd(dummyprevdir,MAX_SIZE);
        // printf("cd ing from %s",dummyprevdir);
        // int dirchange=cd(startdir,prevdir);
        int dirchange=cd();
        if(dirchange)
            strcpy(prevdir,dummyprevdir);
        return 0;
    }
    else if(strcmp(realcommand,"ls")==0)
    {
        // printf("strcmp success\n");
        ls();
        return 0;
    }
    else if(strcmp(realcommand,"repeat")==0)
    {
        repeat(stored);
        return 0;
    }
    else if(strcmp(realcommand,"quit")==0)
    {
        return 1;
    }
    else if(strcmp(realcommand,"pinfo")==0)
    {
        pinfo();
        return 0;
    }
    else if(strcmp(realcommand,"history")==0)
    {
        displayhistory(*stored);
        return 0;
    }
    else if(strcmp(realcommand,"jobs")==0)
    {
        char* flag=strtok(NULL," \t\n");
        if(flag==NULL)
            jobs(1,1);
        else if(strcmp(flag,"-r")==0)
        {
            jobs(1,0);
        }
        else if(strcmp(flag,"-s")==0)
        {
            jobs(0,1);
        }
        else
            printf("Invalid flag: %s\n",flag);
        return 0;
    }
    else if(strcmp(realcommand,"sig")==0)
    {
        char* jobstr=strtok(NULL," \t\n");
        if(jobstr==NULL)
        {
            printf("invalid format (sig <jobnumber> <signalnumber>)\n");
            return 0;
        }
        int jobid=atoi(jobstr);
        char* sigstr=strtok(NULL," \t\n");
        if(sigstr==NULL)
        {
            printf("invalid format (sig <jobnumber> <signalnumber>)\n");
            return 0;
        }
        int sigid=atoi(sigstr);
        sig(jobid,sigid);
        return 0;
    }
    else if(strcmp(realcommand,"fg")==0)
    {
        char* job=strtok(NULL," \t\n");
        fg(job);
        return 0;
    }
    else if(strcmp(realcommand,"bg")==0)
    {
        char* job=strtok(NULL," \t\n");
        bg(job);
        return 0;
    }
    else if(strcmp(realcommand,"replay")==0)
    {
        replay(stored);
        return 0;
    }
    else 
    {
        char* args[MAX_SIZE];
        // char** args=(char**)malloc(MAX_SIZE*sizeof(char*));
        args[0]=(char*)malloc(strlen(realcommand));
        strcpy(args[0],realcommand);
        // printf("copied into args as %s\n",args[0]);
        int i=1,bg=0;
        char* token= strtok(NULL," \t\n");
        while(token!=NULL)
        {
            if(strcmp(token,"&")==0)
                bg=1;
            else
            {
                args[i]=(char*)malloc(strlen(token));
                strcpy(args[i++],token);
                // printf("args %d: %s\n",i-1,args[i-1]);
            }
            token= strtok(NULL," \t\n");
        }
        // if(i==1)
        //     args[1]=NULL;
        args[i]=NULL;
        if(bg==0)
            fgproc(args,inredir,infile);
            // fgproc(args);
            
        else
            // bgproc(args);
            bgproc(args,inredir,infile);
        // for(int j=0;j<i;j++)
        //     free(args[j]);
        // free(args);
        return 0;
    }
        
}