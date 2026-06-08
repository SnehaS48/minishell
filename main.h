#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUILTIN   1
#define EXTERNAL  2
#define NO_COMMAND 3

/* ANSI colors */
#define ANSI_COLOR_RESET "\x1b[0m"

/* Job structure */
struct Store
{
    int pid;
    char commands[100];
    struct Store *next;
};

/* Function declarations */
void scan_input(char *prompt, char *input_string);
char *get_command(char *input_string);
int check_command_type(char *command);
void execute_internal_commands(char *input_string);
void extract_external_commands(char *input_string);
void signal_handler(int sig_num);

/* Job control */
void display(struct Store *head);
void delete_first(struct Store **head);

extern struct Store *head;
extern int pid;
extern int status;

#endif
