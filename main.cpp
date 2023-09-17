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
    if (id == -1) // fork error
    {
        std::cerr << "Could not fork a process";
        return 2;
    }
    else if (id == 0) // child process
    {
        close(fd[1]);
        int received;
        int status = read(fd[0], &received, sizeof(int));
        int sum = 0;

        while (status != 0)
        {
            if (status == -1)
            {
                std::cerr << "Could not read from pipe\n";
                return 3;
            }

            sum += received;
            status = read(fd[0], &received, sizeof(int));
        }

        close(fd[0]);
        std::cout << "The sum of numbers is: " << sum << std::endl;
    }
    else // parent process
    {
        close(fd[0]);
        int number;

        while (std::cin >> number)
        {
            if (write(fd[1], &number, sizeof(int)) == -1)
            {
                std::cerr << "Could not write into pipe\n";
                return 4;
            }
        }

        close(fd[1]);
    }

    return 0;
}
