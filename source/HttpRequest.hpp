#pragma once
#include <ranges>
#include <unordered_map>
#include <string>
#include <string_view>

class HttpRequest {
public:
    explicit HttpRequest(const std::string& request);
    const std::string& get_method() const { return method_; }
    const std::string& get_path() const { return path_; }
    const std::unordered_map<std::string, std::string>& get_headers() const { 
        return headers_; 
    }
    const std::string& get_body() const { return body_; }
    
    // Helper to get specific header
    std::string get_header(const std::string& key) const {
        auto it = headers_.find(key);
        return it != headers_.end() ? it->second : "";
    }
private:
    void parse(const std::string& request);
    std::string method_;
    std::string path_;
    std::unordered_map<std::string, std::string> headers_;
    std::string body_;
};