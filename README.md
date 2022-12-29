# Minishell

[![Intro](https://img.shields.io/badge/Cursus-Minishell-success?style=for-the-badge&logo=42)](https://github.com/bshintak/Minishell)
 
 [![Stars](https://img.shields.io/github/stars/bshintak/Minishell?color=ffff00&label=Stars&logo=Stars&style=?style=flat)](https://github.com/bshintak/Minishell)
 [![Size](https://img.shields.io/github/repo-size/bshintak/Minishell?color=blue&label=Size&logo=Size&style=?style=flat)](https://github.com/bshintak/Minishell)
 ![Lines of code](https://img.shields.io/tokei/lines/github/bshintak/Minishell?color=blueviolet)
 [![Activity](https://img.shields.io/github/last-commit/bshintak/Minishell?color=red&label=Last%20Commit&style=flat)](https://github.com/bshintak/Minishell)

### Executor
- It receives the tree, the environment and the number of pipes
- Basically checks whether the tree arguments are commands, builtins or redirections
- one_or_two_cmds():
> If the program receives two or more commands - if
> If the program receives only one command - else
- multi_pipes():
> As long as there is node->up (pipes)
- Pipe() > create a pipe (node->p[0] > the read end)(node->p[1] > the write end)

<p align="left">
  <img src=https://raw.githubusercontent.com/bshintak/Minishell/pipe_diagram.png />
</p>

- Fork() > used for creating a new process
> In the event of an error, fork returns -1
> If we see 0 as the return value of fork, we know we are in the child process
> Otherwise if we see a PID, we know we are in the parent (and we don't need this)
- Process():
> First we need the path of the command
> Then we need to create a copy of a file descriptor (dup2(oldfd, newfd))
- Wait_cmd():
> waitpid() > pid: the PID of the child process we should wait for / status: store the child’s exit status / options: we don't need this
> WIFEXITED(status): returns true if the child terminated normally
> WEXITSTATUS(status): to be used only if WIFEXITED returned true (returns the child’s exit code)
> wait() > it receives the status (store the child’s exit status)
