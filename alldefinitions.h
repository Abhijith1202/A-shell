#ifndef ALL_DEF_H
#define ALL_DEF_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define DBLUE "\e[1;34m"
#define CYAN "\x1b[36m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

#define MAX_SIZE 2000

typedef struct procstruct
{
    int pid;
    char name[MAX_SIZE];
}process;

typedef struct job
{
    int jobnumber;
    int pid;
    char jobname[MAX_SIZE];
    char status[MAX_SIZE];
}jobstruct;


process processarray[MAX_SIZE];
// jobstruct jobarray[MAX_SIZE];
int SHELLPID;
int FGPID;
char FGPROCNAME[MAX_SIZE];
char startdir[MAX_SIZE];
char prevdir[MAX_SIZE];
char history[20][MAX_SIZE];
int bgprocdone=0;
int bgend=0;

// typedef struct procstruct process;

typedef long long int lli;
void clear();
void pwd();
// void display(char* startdir);
void display();
void echocall();
// int cd(char* startdir, char* prevdir);
int cd();
void ls();
void lsnl(char* path, int displayhidden);
void filefields(struct tm* timevar, struct stat stvar, char* path);
void lsyl(char* path, int displayhidden);
void fgproc(char **args,int inredir,char* infile);
// void fgproc(char** args);
void bgproc(char** args, int inredir,char* infile);
// void bgproc(char** args);
void pinfo();
// void repeat();
void repeat(int* stored);
// void execute(char* command);
// void cdrepeat(char* path);
int savehistory(int commcount,char command[MAX_SIZE]);
void displayhistory(int stored);
int outredircheck(char* commandredir,char* outfile);
int inredircheck(char* commandredir,char* infile);
int executecom(char* commands ,int* stored, int repeatflag);
void piped(char* commands, int* stored);
char** pipedcommands(char* command);
int checkpiping(char* command);
void jobs(int runflag, int sleepflag);
void bg(char* job);
void fg(char* job);
void shiftjobs(int pos);
void replay(int* stored);
// void checkbgprocess();

#endif
