#include <functional>
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

class Router {
public:
    using HandlerFunc = std::function<HttpResponse(const HttpRequest&)>;
    void add_route(std::string method, std::string path, HandlerFunc handler);
    HttpResponse route(const HttpRequest& request);
private:
    std::unordered_map<std::string, HandlerFunc> routes_; // maps a combined string of method and path to its handler function
};