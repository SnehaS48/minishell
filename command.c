#include "main.h"

char *get_command(char *input_string)
{
    static char buffer[50];
    int i = 0;

    while (input_string[i] != ' ' && input_string[i] != '\0')
    {
        buffer[i] = input_string[i];
        i++;
    }
    buffer[i] = '\0';
    return buffer;
}

int check_command_type(char *cmd)
{
    char *builtins[] = {"cd", "pwd", "exit", "echo", "jobs", "fg", "bg", NULL};

    for (int i = 0; builtins[i]; i++)
        if (strcmp(cmd, builtins[i]) == 0)
            return BUILTIN;

    return EXTERNAL;
}

extern struct Store *head;

void display(struct Store *head)
{
    if (head == NULL)
        return;

    struct Store *temp = head;
    while (temp != NULL)
    {
        printf("%d\t%s\n", temp->pid, temp->commnds);
        temp = temp->next;
    }
}
void delete_first(struct Store **head)
{
    if (*head == NULL)
    {
        return; // list is empty
    }

    struct Store *temp = *head;
    *head = (*head)->next;  // move head to next node
    free(temp);             // free old first node
}
