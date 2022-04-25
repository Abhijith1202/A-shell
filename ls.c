
#include "alldefinitions.h"

void lsnl(char* path,int displayhidden)
{
    struct dirent* d;
    DIR* dir;
    dir=opendir(path);
    if(!dir)
    {
        FILE *isfile=fopen(path,"r");
        if(isfile)
        {
            printf("%s\n",path);
            // return;
        }
        else
        {
            printf("%s: No such file/directory\n",path);
        }
        return;
    }

    while((d=readdir(dir))!=NULL)
    {
        if(displayhidden==1 || (displayhidden==0 && d->d_name[0]!='.'))
            printf("%s\n",d->d_name);
    }
    closedir(dir);
}

void filefields(struct tm* timevar, struct stat stvar, char* filename)
{
    char type;
    char datetime[MAX_SIZE];
    if(S_ISREG(stvar.st_mode))
    {
        type = '-';
    }
    else if(S_ISDIR(stvar.st_mode))
    {
        type = 'd';
    }

    else if(S_ISCHR(stvar.st_mode))
    {
        type = 'c';
    }

    else if(S_ISBLK(stvar.st_mode))
    {
        type = 'b';
    }
    
    else if(S_ISFIFO(stvar.st_mode))
    {
        type = 'f';
    }

    else if(S_ISLNK(stvar.st_mode))
    {
        type = 'l';
    }

    else if(S_ISSOCK(stvar.st_mode))
    {
        type = 's';
    }

    printf("%c",type);
    printf((stvar.st_mode & S_IRUSR) ? "r" : "-");
    printf((stvar.st_mode & S_IWUSR) ? "w" : "-");
    printf((stvar.st_mode & S_IXUSR) ? "x" : "-");
    printf((stvar.st_mode & S_IRGRP) ? "r" : "-");
    printf((stvar.st_mode & S_IWGRP) ? "w" : "-");
    printf((stvar.st_mode & S_IXGRP) ? "x" : "-");
    printf((stvar.st_mode & S_IROTH) ? "r" : "-");
    printf((stvar.st_mode & S_IWOTH) ? "w" : "-");
    printf((stvar.st_mode & S_IXOTH) ? "x" : "-");
    printf("%3d", (int)stvar.st_nlink);
    char* uname=(getpwuid(stvar.st_uid)->pw_name);
    char* grpname=(getgrgid(stvar.st_gid)->gr_name);
    // char* filename=d->d_name;
    // char* filename;
    // strcpy(filename,path);
    lli filesize=(lli)stvar.st_size;
    printf(" %8s",uname);
    printf(" %8s",grpname);
    printf("%10lld",filesize);
    timevar=localtime(&stvar.st_mtime);
    strftime(datetime,MAX_SIZE,"%b %d %H:%M",timevar);
    if(datetime[4]=='0')
        datetime[4]=' ';
    printf(" %s %s\n",datetime,filename);
}

void lsyl(char* path, int displayhidden)
{
    struct dirent* d;
    DIR* dir;
    dir=opendir(path);
    struct stat stvar;
    struct tm* timevar;
    char datetime[MAX_SIZE];

    if(!dir)
    {
        // perror(path);
        FILE* isfile=fopen(path,"r");
        if(isfile)
        {
            // printf("file opened\n");
            stat(path,&stvar);
            filefields(timevar,stvar,path);
        }
        else
        {
            printf("%s: No such file/directory\n",path);
        }
        return;
    }
    lli total=0;
    while((d=readdir(dir))!=NULL)
    {
        char newdir[MAX_SIZE];
        strcpy(newdir,path);
        strcat(newdir,"/");
        strcat(newdir,d->d_name);

        stat(newdir,&stvar);
        if(displayhidden==1 || d->d_name[0]!='.')
        {
            total+=stvar.st_blocks;
        }
    }
    printf("total %lld\n",total/2);
    closedir(dir);
    dir=opendir(path);

    while((d=readdir(dir))!=NULL)
    {
        char newdir[MAX_SIZE];
        strcpy(newdir,path);
        strcat(newdir,"/");
        strcat(newdir,d->d_name);

        stat(newdir,&stvar);
        if(displayhidden==1 || d->d_name[0]!='.')
        {
            char type;
            if(S_ISREG(stvar.st_mode))
            {
                type = '-';
            }
            else if(S_ISDIR(stvar.st_mode))
            {
                type = 'd';
            }

            else if(S_ISCHR(stvar.st_mode))
            {
                type = 'c';
            }

            else if(S_ISBLK(stvar.st_mode))
            {
                type = 'b';
            }
            
            else if(S_ISFIFO(stvar.st_mode))
            {
                type = 'f';
            }

            else if(S_ISLNK(stvar.st_mode))
            {
                type = 'l';
            }

            else if(S_ISSOCK(stvar.st_mode))
            {
                type = 's';
            }

            printf("%c",type);
            printf((stvar.st_mode & S_IRUSR) ? "r" : "-");
            printf((stvar.st_mode & S_IWUSR) ? "w" : "-");
            printf((stvar.st_mode & S_IXUSR) ? "x" : "-");
            printf((stvar.st_mode & S_IRGRP) ? "r" : "-");
            printf((stvar.st_mode & S_IWGRP) ? "w" : "-");
            printf((stvar.st_mode & S_IXGRP) ? "x" : "-");
            printf((stvar.st_mode & S_IROTH) ? "r" : "-");
            printf((stvar.st_mode & S_IWOTH) ? "w" : "-");
            printf((stvar.st_mode & S_IXOTH) ? "x" : "-");
            printf("%3d", (int)stvar.st_nlink);
            char* uname=(getpwuid(stvar.st_uid)->pw_name);
            char* grpname=(getgrgid(stvar.st_gid)->gr_name);
            char* filename=d->d_name;
            lli filesize=(lli)stvar.st_size;
            printf(" %8s",uname);
            printf(" %8s",grpname);
            printf("%10lld",filesize);
            timevar=localtime(&stvar.st_mtime);
            strftime(datetime,MAX_SIZE,"%b %d %H:%M",timevar);
            if(datetime[4]=='0')
                datetime[4]=' ';
            printf(" %s %s\n",datetime,filename);
        }
    }
    closedir(dir);
}


void ls()
{
    // printf("reached ls\n");
    char argument[MAX_SIZE][MAX_SIZE];
    int argno=0;
    char* token;
    for(int i=0;i<MAX_SIZE;i++)
    {
        token=strtok(NULL," \t\n");
        if(token==NULL)
        {
            argno=i;
            break;
        }
        strcpy(argument[i],token);
    }
    char dest[MAX_SIZE][MAX_SIZE];
    int destcount=0;
    dest[destcount][0]='.';
    dest[destcount][1]='\0';
    int lflag=0,aflag=0;
    for(int i=0;i<argno;i++)
    {
        if(strcmp(argument[i],"\0")==0)
            break;
        if(argument[i][0]=='-')
        {
            for(int j=1;argument[i][j]!='\0';j++)
            {
                if(argument[i][j]=='a')
                    aflag=1;
                else if(argument[i][j]=='l')
                    lflag=1;
                else
                {
                    printf("invalid flag %s\n",argument[i]);
                    return;
                }
            }
        }
        else
            strcpy(dest[destcount++],argument[i]);
    }
    destcount=(destcount==0?1:destcount);
    char realdest[destcount][MAX_SIZE];
    for(int i=0;i<destcount;i++)
    {
        if(dest[i][0]=='~')
        {
            strcpy(realdest[i],startdir);
            strcat(realdest[i],"/");
            strcat(realdest[i],&dest[i][1]);
        }
        else
        {
            strcpy(realdest[i],dest[i]);
        }
        if(destcount>1)
            printf("%s:\n",dest[i]);
        if(lflag==1 && aflag==1)
            lsyl(realdest[i],1);
        else if(lflag==1)
            lsyl(realdest[i],0);
        else if(aflag==1)
            lsnl(realdest[i],1);
        else
            lsnl(realdest[i],0);
    }
}