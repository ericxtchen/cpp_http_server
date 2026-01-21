#pragma once
#include <string>
#include <unordered_map>

class HttpResponse { // maybe use a builder pattern?
public:
    class Builder;
    std::string to_string() const;
private:
    HttpResponse() = default;

    int status_code_ = 200;
    std::string status_text_ = "OK";
    std::unordered_map<std::string, std::string> headers_;
    std::string body_;

    friend class Builder;
};

class HttpResponse::Builder {
public:
    Builder() = default;

    Builder& status_code(int code) {
        response_.status_code_ = code;
        response_.status_text_ = get_status_text(code);
        return *this;
    }

    Builder& headers(const std::string& key, const std::string& value) {
        response_.headers_.emplace(key, value);
        return *this;
    }

    Builder& body(const std::string& body) {
        response_.body_ = body;
        return *this;
    }

    HttpResponse build() {
        if (!response_.body_.empty() && response_.headers_.find("Content-Length") == response_.headers_.end()) {
            response_.headers_["Content-Length"] = std::to_string(response_.body_.size());
        }

        return response_;
    }

private:
    HttpResponse response_;
    static std::string get_status_text(int code) {
        switch (code) {
            case 200:
                return "OK";
            case 201:
                return "Created";
            case 404:
                return "Not Found";
            case 500:
                return "Internal Server Error";
            default:
                return "Unknown";
        }
    }
};