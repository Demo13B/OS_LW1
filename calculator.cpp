#include <fstream>
#include <iostream>
#include <unistd.h>

auto main() -> int
{
    std::ofstream output;
    output.open("./output.txt");
    std::string received;
    int sum = 0;

    while (read(STDIN_FILENO, &received, sizeof(received)) != 0)
    {
        sum += std::stoi(received);
    }

    output << "Summ is: " << sum << "\n";
}
