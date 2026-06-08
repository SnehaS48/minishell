# MiniShell — Linux Shell Implementation in C

MiniShell is a custom Linux shell application developed in C to simulate core functionalities of a Unix terminal environment. The project was designed and implemented on Ubuntu Linux using system calls, process management, IPC mechanisms, and signal handling concepts.

## Features

* Command execution using `fork()` and `exec()`
* Foreground and background process handling
* Signal handling (`SIGINT`, `SIGTSTP`, `SIGCHLD`)
* Command parsing and tokenization
* Linux terminal interaction
* Process synchronization

## Technologies Used

* C Programming
* Linux (Ubuntu)
* System Calls
* IPC Mechanisms
* Signal Handling
* GDB
* GCC
* Makefile

## Key Concepts

* Process Management
* Concurrent Programming
* Linux System Programming
* Debugging and Testing
* Modular Software Design

## How to Compile

```bash
gcc *.c -o minishell
```

## How to Run

```bash
./minishell
```

## Outcome

This project strengthened understanding of Linux internals, operating system concepts, process handling, debugging, and software development lifecycle practices.
