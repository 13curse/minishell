### minishell 🐚​

This project is all about recreating your own **(mini)shell**, taking Bash as a reference.
The goal is to implement a **command-line interpreter** with core functionalities similar to those found in Bash.

## Features
**Command execution:** Execute simple commands and builtins.

**Environment variables:** Handle environment variables (e.g., PATH, HOME, etc.).

**Special characters:** Manage special characters such as spaces, tabs, quotes, etc.

**Redirections:** Support input/output redirections (<, >, >>, <<).

**Pipes:** Handle pipes (|) for chaining commands.

**Signals:** Manage signals (e.g., Ctrl-C, Ctrl-D, Ctrl-\).

**History:** Implement command history (using our own readline).

**Custom readline:** Recoded a simplified version of readline for command input.

## Bonus features:

**Logical operators:** Support for && (AND) and || (OR) between commands.

## Getting Started

**Prerequisites**

• C compiler (e.g., gcc or clang)

• Make

• Readline library (for the original version, but our custom readline is used here)

**Installation**

Clone the repository:

``` git clone <your-repository-url> ```

``` cd minishell ```

Build the project:

``` make ```

``` make re ```

Run minishell:

``` ./minishell ```

**Usage**

• Enter commands as you would in Bash.

• Use pipes, redirections, and logical operators.

• Manage environment variables.

• Use Ctrl-C to interrupt a command, Ctrl-D to exit the shell.

## Custom readline

We have recoded a simplified version of the readline library to handle command input, including:

• Command line editing

• History navigation

• Basic line editing features

## Bonus Features

Logical operators:

• command1 && command2 — execute command2 only if command1 succeeds.

• command1 || command2 — execute command2 only if command1 fails.

## Authors
@sbehar && @van-nguy
