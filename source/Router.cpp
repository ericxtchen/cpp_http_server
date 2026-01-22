#include "Router.hpp"

void Router::add_route(std::string method, std::string path, HandlerFunc handler) {
    std::string composite = method + " " + path;
    routes_.emplace(composite, handler);
}

HttpResponse Router::route(const HttpRequest& request) {
    std::string key = request.get_method() + " " + request.get_path();
    if (routes_.contains(key)) {
        HandlerFunc handler = routes_[key];
        return handler(request);
    } else {
        return HttpResponse::Builder().status_code(404).build(); // return 404 if no handler can be found
    }
}