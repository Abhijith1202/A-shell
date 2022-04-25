#include "alldefinitions.h"

int outredircheck(char* commandredir,char* outfile)
{
    for(int i=0; commandredir[i]!='\0';i++)
    {
        if(commandredir[i]=='>')
        {
            if(commandredir[i+1]=='>')
            {
                i+=2;
                while(commandredir[i]!='\0' && commandredir[i]==' ')
                {
                    i++;
                }
                int j=i;
                for(;commandredir[j]!='\0' && commandredir[j]!='\n' && commandredir[j]!=' ' && commandredir[j]!='<' && commandredir[j]!='|';j++)
                {
                    outfile[j-i]=commandredir[j];
                }
                outfile[j-i]='\0';
                return 2;
            }
            i++;
            while(commandredir[i]!='\0' && commandredir[i]==' ')
                {
                    i++;
                }
            int j=i;
            for(;commandredir[j]!='\0' && commandredir[j]!='\n' && commandredir[j]!=' ' && commandredir[j]!='<' && commandredir[j]!='|';j++)
            {
                outfile[j-i]=commandredir[j];
            }
            outfile[j-i]='\0';
            return 1;
        }
    }
    return 0;
}

int inredircheck(char* commandredir,char* infile)
{
    for(int i=0; commandredir[i]!='\0';i++)
    {
        if(commandredir[i]=='<')
        {
            i++;
            while(commandredir[i]!='\0' && commandredir[i]==' ')
                {
                    i++;
                }
            int j=i;
            for(;commandredir[j]!='\0' && commandredir[j]!='\n' && commandredir[j]!=' ' && commandredir[j]!='>' && commandredir[j]!='|';j++)
            {
                infile[j-i]=commandredir[j];
            }
            infile[j-i]='\0';
            return 1;
        }
    }
    return 0;
}