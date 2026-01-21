#include "HttpResponse.hpp"
#include <sstream>

std::string HttpResponse::to_string() const {
    std::ostringstream oss;

    oss << "HTTP/1.1" << status_code_ << status_text_ << "\r\n";

    for (const auto& [key, value] : headers_) {
        oss << key << ": " << value << "\r\n";
    }

    oss << "\r\n";

    oss << body_;

    return oss.str();
}