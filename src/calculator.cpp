#include <fcntl.h>
#include <unistd.h>
#include <string>

auto main() -> int {
    int outputd;
    outputd = open("output.txt", O_WRONLY, 0);
    std::string received;
    int sum = 0;

    while (read(STDIN_FILENO, &received, sizeof(received)) != 0) {
        sum += std::stoi(received);
    }

    std::string sum_str = std::to_string(sum);

    char output[100];
    sprintf(output, "The sum is: %d", sum);

    if (write(outputd, &output, 12 + sum_str.length()) == -1) {
        return 1;
    }
}
