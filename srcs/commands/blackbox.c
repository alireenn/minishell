// how to execute a pipe?

pid_t pid;
int fd[2];

pipe(fd);
pid = fork();

if(pid==0)
{
    dup2(fd[WRITE_END], STDOUT_FILENO);
    close(fd[READ_END]);
    close(fd[WRITE_END]);
    execlp(firstcmd, firstcmd, frsarg, (char*) NULL);
    fprintf(stderr, "Failed to execute '%s'\n", firstcmd);
    exit(1);
}
else
{ 
    pid=fork();

    if(pid==0)
    {
        dup2(fd[READ_END], STDIN_FILENO);
        close(fd[WRITE_END]);
        close(fd[READ_END]);
        execlp(scmd, scmd, secarg,(char*) NULL);
        fprintf(stderr, "Failed to execute '%s'\n", scmd);
        exit(1);
    }
    else
    {
        int status;
        close(fd[READ_END]);
        close(fd[WRITE_END]);
        waitpid(pid, &status, 0);
    }
}


