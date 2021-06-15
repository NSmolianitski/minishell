# Minishell
Minishell is a project that aims to emulate bash behavior.

## Builtins

- echo with option `-n`
- cd with only a relative or absolute path
- pwd without any options
- export without any options
- unset without any options
- env without any options and any arguments
- exit without any options

## Main functions

- searches and launches the right executable (based on the PATH variable or by using relative or absolute path) like in bash
- `;` in the command separates commands like in bash
- quotes work like in bash (except for multiline commands)
- redirections `< > >>` work like in bash except for file descriptor aggregation
- pipes work like in bash
- environment variables work like in bash
- $? works like in bash
- signals (ctrl + C, ctrl + D, ctrl + \\) works like in bash

## What I learned

- a lot about pipes and file descriptors
- parsing principles
- some things about environment variables and bash
