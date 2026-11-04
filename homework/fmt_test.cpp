
#include <fmt/format.h>
#include <string>

int main() {
    // 1. 测试 fmt::print
    fmt::print("Hello, fmt!\n");

    int a = 10;
    int b = 20;
    fmt::print("{} + {} = {}\n", a, b, a + b);

    // 2. 测试 fmt::format
    std::string message =
        fmt::format("My name is {}, age is {}", "Yilang Li", 18);

    fmt::print("{}\n", message);

    // 3. 测试浮点数格式化
    double pi = 3.1415926;
    fmt::print("Pi = {:.2f}\n", pi);

    return 0;
}
