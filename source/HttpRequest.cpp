#include "HttpRequest.hpp"

HttpRequest::HttpRequest(const std::string& request) {
    parse(request);
}

void HttpRequest::parse(const std::string& request) {
    size_t first_line_end = request.find("\r\n");
    std::string request_line = request.substr(0, first_line_end);
    
    size_t first_space = request_line.find(' ');
    size_t second_space = request_line.find(' ', first_space + 1);
    
    method_ = request_line.substr(0, first_space);
    path_ = request_line.substr(first_space + 1, second_space - first_space - 1);

    size_t headers_end = request.find("\r\n\r\n", first_line_end);
    std::string headers_str = request.substr(first_line_end + 2, headers_end - first_line_end - 2);

    std::string_view sv(headers_str);
    auto lines = sv | std::views::split(std::string_view("\r\n"));
    for (auto&& line_view : lines) {
        std::string_view line(line_view.begin(), line_view.end());
        if (line.empty()) break;
        size_t colon = line.find(":");
        if (colon != std::string_view::npos) {
            std::string key(line.substr(0, colon));
            size_t value_start = colon + 1;
            while (value_start < line.size() && line[value_start] == ' ') {
                value_start++;
            }
            std::string value(line.substr(value_start));
            headers_.emplace(key, value);
        }
    }

    if (headers_end != std::string::npos) {
        body_ = request.substr(headers_end + 4); // + 4 for the \r\n\r\n
    }
}
