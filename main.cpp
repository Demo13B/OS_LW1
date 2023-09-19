#include <unistd.h>
#include <string>

auto main() -> int {
    int fd[2];  // fd[0] - read; fd[1] - write
    // Creating pipe and checking that it was created
    if (pipe(fd) == -1) {
        return 1;
    }

    // Forking the process
    int id = fork();

    if (id == -1) {  // fork error
        return 2;
    } else if (id == 0) {  // child process
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);

        execlp("./calculator", "./calculator", NULL);

        return 3;
    } else {  // parent process
        close(fd[0]);
        std::string number = "";
        char c;

        if (read(STDIN_FILENO, &c, sizeof(char)) == -1) {
            return 4;
        }

        while (c != '\n') {
            if (c == ' ') {
                if (write(fd[1], &number, sizeof(number)) == -1) {
                    return 5;
                }
                number = "";
            } else {
                number += c;
            }

            if (read(STDIN_FILENO, &c, sizeof(char)) == -1) {
                return 4;
            }
        }

        if (number != "") {
            if (write(fd[1], &number, sizeof(number)) == -1) {
                return 5;
            }
        }

        close(fd[1]);
    }

    return 0;
}
