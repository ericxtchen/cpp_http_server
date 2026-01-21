#include <ranges>
#include <iostream>
#include <string>
#include <string_view>

int main() {
    std::string_view sv = "hello\r\nworld";
    auto lines = sv | std::views::split(std::string_view("\r\n"));
    
    for (auto line : lines) {
        std::cout << "line\n";
    }
}