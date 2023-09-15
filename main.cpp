#include <iostream>
#include <unistd.h>

auto main() -> int
{
    int fd[2]; // fd[0] - read; fd[1] - write
    // Creating pipe and checking that it was created
    if (pipe(fd) == -1)
    {
        std::cerr << "Pipe creation failed\n";
        return 1;
    }

    // Forking the process
    int id = fork();
    if (id == 0)
    {
        close(fd[1]);
        int y;
        if (read(fd[0], &y, sizeof(typeof(y))) == -1)
        {
            std::cerr << "Could not read from pipe\n";
            return 2;
        }
        close(fd[0]);
        std::cout << "Received form parent: " << y << std::endl;
    }
    else
    {
        close(fd[0]);
        int x;
        std::cin >> x;
        if (write(fd[1], &x, sizeof(typeof(x))) == -1)
        {
            std::cerr << "Could not write into pipe\n";
            return 3;
        }
        close(fd[1]);
    }

    return 0;
}
