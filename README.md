# Minishell

## Introduction

Minishell is a simple shell implementation written in C as part of the 42 curriculum. This project was developed collaboratively by Pedro and Gabriel. The goal was to create a functional shell that mimics basic behaviors of Bash while reinforcing our understanding of processes, file descriptors and system calls.

## Features

- Displays a prompt while waiting for user input

- Implements a working command history

- Executes commands using absolute paths, relative paths or based on the PATH environment variable

- Supports input and output redirections (<, >, <<, >>)

- Implements pipes (|) to connect command outputs to inputs

- Expands environment variables ($VARIABLE)

- Handles exit status ($?)

- Properly manages signals:

	- Ctrl-C: Displays a new prompt on a new line

	- Ctrl-D: Exits the shell

	- Ctrl-\: Does nothing in interactive mode

- Implements the following built-in commands:

	- echo (with -n option)

	- cd (with relative or absolute paths)

	- pwd

	- export

	- unset

	- env

	- exit

# Usage
`$ git clone https://github.com/gabzaf/minishell.git`

`$ cd minishell`

## Compile the project
`$ make`

## Run the shell
`$ ./minishell`

### Run a command
`$ echo "Hello, world!"`

### Change directory
`$ cd /home/user`

### View environment variables
`$ env`

### Redirect output to a file
`$ ls > output.txt`

### Use pipes
`$ grep "error" log.txt | sort | uniq`

#### Technical Details

- Written in C

- Uses readline for input handling

- Implements command execution using fork() and execve()

- Manages processes using pipes and redirections

- Handles signals properly for interactive mode

## Known Limitations

- Does not support advanced shell features such as job control

- Limited handling of syntax errors

- Readline may cause memory leaks (permitted by project guidelines)

# Authors

Pedro Monteiro

Gabriel Affonso

### License

This project is developed as part of the 42 curriculum and follows its academic policies.

# Real-World Applications of Minishell Concepts

The skills and concepts implemented in Minishell—such as command execution, process management, pipes, redirections, signal handling, and environment variable manipulation—are not just academic exercises. They form the backbone of many practical applications across industries like cybersecurity, systems programming, DevOps, and beyond.

## Why Companies Care
The knowledge gained from Minishell directly translates to skills in demand by industries that rely on secure, efficient and scalable systems. Whether it’s a cybersecurity firm hunting vulnerabilities, a DevOps team streamlining deployments or a tech giant optimizing cloud infrastructure, the ability to manipulate and understand shell behavior is a critical asset. For someone passionate about cybersecurity and red teaming, this project lays a foundation for scripting exploits, analyzing attack surfaces, and mastering system-level security challenges.

