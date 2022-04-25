# A-shell (Abhi's shell)

## How to run:
- Extract the file into a folder
- on the terminal, type `make`
- type `./a.out` to start using A shell :)

### Files in the folder:
    * main.c            : the code which provides the interface of the shell
    * execute.c         : the code which handles the functional interface of the shell
    * alldefinitions.h  : contains all the headers and function definitions
    * library.h         : a header file that includes all the below files, for ease of compilation.
    * display.c         : the function for printing the prompt of the shell
    * pwd.c             : The function that mimics the `pwd` command: prints the working directory
    * cd.c              : cd command, ie, change directory
    * clear.c           : clear command
    * echo.c            : echo command: printing the provided string into the terminal
    * ls.c              : ls [-l,-a,-la] command
    * fgproc.c          : the function that handles foreground system commands
    * bgproc.c          : the function that handles background system commands
    * repeat.c          : the repeat command
    * pinfo.c           : pinfo command: gives the info avout processes
    * history.c         : the code for storing and using history command
    * redirection.c     : the code for handling input and output redirections.
    * jobs.c            : code for jobs function
    * fg.c              : code for the fg function
    * bg.c              : code for the bg function
    * replay.c          : code for the replay function


### Functions that work on Ashell:
    * pwd                       : prints the current working directory
    * cd <path>                 : changes the directory to the directory mentioned by the path. if no path is given, it returns to the directory where the shell was run from
    * echo <string>             : prints the string, by neglecting the extra spaces in the provided string.
    * ls [-a,-l,-la] [path]     : lists the subfolders and files in the directory provided to by the path. Can print hidden files (-a) and details about them(-l).
    * clear                     : clears the terminal
    * repeat <count> <command>  : repeats the command mentioned count number of times
    * pinfo [pid]               : prints the info about the process mentioned by the pid, of about the shell process if pid is not provided
    * history [number]          : displays <number> number of commands used previously (here, number<20). If number if not provided, prints 10 commands used earlier.
    * jobs [flags]              : lists the background processes of the shell. if flags -r or -s are given, lists only those processes that are running or terminated respectively.
    * fg <jobnumber>            : brings the background process with the given job number to the foreground
    * bg <jobnumber>            : sends signal to make a backgrount process to run in the background.
    * sig <jobnumber> <signal>  : sends the signal corresponding to the 'signal' number to the process with job id as 'jobnumber'
    * replay -command <command> -interval <interval> -period <period>
                                : executes the command specified after the command flag after every 'interval' seconds, for 'period' seconds. 
    * quit                      : saves the history and ends the shell session.        