#include "alldefinitions.h"
// void display(char* startdir)
void display()
{
    char system[MAX_SIZE],currentpath[MAX_SIZE];
    char*uname;
    uname=getenv("LOGNAME");
    gethostname(system,MAX_SIZE);
    getcwd(currentpath,MAX_SIZE);

    int l1=strlen(startdir);
    int l2=strlen(currentpath);
    int i=0;
    for(i=0;i<l1 && i<l2; i++)
    {
        if(startdir[i]!=currentpath[i])
            break;
    }

    if (i==l1)
    {
        if(l1==l2 || currentpath[l1]=='/')
        {
            currentpath[0]='~';
            int j=l1;
            for(j=l1;j<l2;j++)
            {
                currentpath[j-l1+1]=currentpath[j];
            }
            currentpath[l2-l1+1]='\0';
        }
    }

    printf(DBLUE "%s" CYAN "@%s:" GREEN "%s>" RESET,uname,system,currentpath);
    if(bgprocdone==1)
        return;
}