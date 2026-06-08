#include "main.h"
#include<window.h>

int main()
{
    char prompt[] = "minishell$ ";
    char input_string[100];

    system("clear");
    scan_input(prompt, input_string);
    return 0;
}
