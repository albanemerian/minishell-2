#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void exec_cmd(char **arr) {
    execvp(arr[0], arr);
    perror("execvp");
    exit(1);
}

void exec_pipe(shell_t *shell, char **env, char *line1, char *line2) {
    char **arr1 = fill_array(line1);
    char **arr2 = fill_array(line2);
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) { // Child process
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        exec_cmd(shell, env, arr1);
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) { // Parent process
        waitpid(pid, NULL, 0);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        // Use sed to add ANSI escape codes for color highlighting
        execlp("grep", "grep", "--color=always", "tty", NULL);
        perror("execlp");
        exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid2, NULL, 0);
}
