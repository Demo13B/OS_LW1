#include <fstream>
#include <iostream>
#include <unistd.h>

auto main() -> int
{
    std::ofstream output;
    output.open("./output.txt");
    int received;
    int sum = 0;

    while (std::cin >> received)
    {
        output << "I read from parent to child: " << received << "\n";
    }
}
