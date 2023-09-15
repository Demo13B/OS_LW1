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
        int status = read(fd[0], &y, sizeof(typeof(y)));
        std::cout << "Numbers from parent: ";
        while (status != 0)
        {
            if (status == -1)
            {
                std::cerr << "Could not read from pipe\n";
                return 2;
            }
            std::cout << y << " ";
            status = read(fd[0], &y, sizeof(typeof(y)));
        }
        close(fd[0]);
        std::cout << std::endl;
    }
    else
    {
        close(fd[0]);
        int number;
        while (std::cin >> number)
        {
            if (write(fd[1], &number, sizeof(int)) == -1)
            {
                std::cerr << "Could not write into pipe\n";
                return 3;
            }
        }
        close(fd[1]);
    }

    return 0;
}
