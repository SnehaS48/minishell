#include "main.h"

extern int pid;
extern int status;

void scan_input(char *prompt)
{
    char input[200];

    while (1)
    {
        printf("%s", prompt);
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL)
            continue;

        input[strcspn(input, "\n")] = '\0';

        if (strncmp(input, "PS1=", 4) == 0)
        {
            strcpy(prompt, input + 4);
            strcat(prompt, " ");
            continue;
        }

        char *cmd = get_command(input);
        int type = check_command_type(cmd);

        if (type == BUILTIN)
            execute_builtin(input, prompt);
        else
            execute_external(input);
    }
}



void execute_internal_commands(char *input_string)
{
    char buffer[256];

    if(strcmp(input_string,"pwd")==0)
    {
        if(getcwd(buffer,sizeof(buffer))!=NULL);
        printf("%s\n",buffer);
        else
        perror("pwd");

    }
    else if(strncmp(input_string,"cd")==0)
    {
         char *home=getenv("home");
         if(home==NULL)
         {
            printf("cd: HOME not set\n");
            return;
         }
         if(chdir(home)!=0)
         {
            perror("cd");
            return;
         }
        if(getcwd(buffer1,sizeof(buffer))!=NULL)
        printf("%s\n",buffer);
    }
    else if(strcmp("exit",input_string)==0)
    {
        exit(0);
    }
    else if(strcmp(input_string,"echo $$")==0)
    {
        printf("%d\n",getpid());
    }
    else if(strcmp(input_string,"echo $?")==0)
    {
        if(WIFEXITED(status))
        printf("%d\n",WEXITSTATUS(status));
    }
    else if(strcmp(input_string,"fg")==0)
    {
        if(head==NULL)
        {
            printf("FG: NO JOBS PRESENT\n");
            return;
        }

        pid=head->pid;
        kill(pid,SIGCONT);
        waitpid(pid,&status,WUNTRACED);
        delete_first(&head);
    }
    else if(strcmp(input_string,"bg")==0)
    {
         if(head==NULL)
        {
            printf("FG: NO JOBS PRESENT\n");
            return;
        }

        kill(head->pid,SIGCONT);

    }
    else if(strcmp(input_string,"echo $SHELL")==0)
    {
        char *shell=getenv("SHELL");
        if(shell!=NULL)
        {
            printf("%s\n",shell);
        }
    }
    else if (strcmp(input_string, "jobs") == 0)
    {
        display(head);
    }
    else if (strncmp(input_string, "cd ", 3) == 0)
    {
        if (chdir(input_string + 3) != 0)
        {
            perror("cd");
            return;
        }

        if (getcwd(buffer1, sizeof(buffer1)) != NULL)
            printf("%s\n", buffer1);
    }

}
void extract_external_commands(char **external_commands)
{
    char *cmds[10][20];
    int cmd = 0, arg = 0;
    int pipe_count = 0;

    external_command[strcspn(external_command, "\n")] = '\0';

    char *token = strtok(external_command, " ");
    while (token != NULL)
    {
        if (strcmp(token, "|") == 0)
        {
            cmds[cmd][arg] = NULL;   
            cmd++;
            arg = 0;
            pipe_count++;
        }
        else
        {
            cmds[cmd][arg++] = token;
        }
        token = strtok(NULL, " ");
    }
    cmds[cmd][arg] = NULL;          
    
    if (pipe_count == 0)
    {
        pid=fork();
        if (pid == 0)
        {
            signal(SIGINT,SIG_DFL);
            signal(SIGTSTP,SIG_DFL);
            signal(SIGCHILD,SIG_DFL);
            execvp(cmds[0][0], cmds[0]);
            perror("execvp failed");
            exit(1);
        }
        else
        {
            wait(pid,&status,WUNTRACED);
        }
        return;
    }

    else
    {
        int total_cmds = pipe_count + 1;
        int fd[2];
        int prev_fd = 0;

        for (int i = 0; i < total_cmds; i++)
        {
            pipe(fd);

            if (pid == 0)
            {
               signal(SIGINT,SIG_DFL);
               signal(SIGTSTP,SIG_DFL);
               signal(SIGCHILD,SIG_DFL);
                dup2(prev_fd, 0);          // stdin
                if (i != total_cmds - 1)
                 dup2(fd[1], 1);       // stdout

                close(fd[0]);
                execvp(cmds[i][0], cmds[i]);
                perror("execvp");
                exit(1);
            }
            else
            {
                wait(pid,&status,WUNTRACED);
                close(fd[1]);
                prev_fd = fd[0];
            }
        }
    }
}

void signal_handler(int sig_num)
{
    if(sig_num,SIGINT)
    {
    printf("%s\n",prompt);
    }
    else if(sig_num==SIGTSTP)
    {
        if(ret==0)
        printf("%s\n",prompt);
    }

}

