#include <iostream>
#include <cassert>
#include "../source/Router.hpp"
#include "../source/HttpRequest.hpp"
#include "../source/HttpResponse.hpp"

void test_basic_routing() {
    Router router;
    
    // Add a simple route
    router.add_route("GET", "/", [](const HttpRequest& req) {
        return HttpResponse::Builder()
            .status_code(200)
            .body("Home page")
            .build();
    });
    
    // Create a fake request
    std::string raw_request = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n";
    HttpRequest request(raw_request);
    
    // Route it
    HttpResponse response = router.route(request);
    std::string response_str = response.to_string();
    
    // Check the response
    assert(response_str.find("200") != std::string::npos);
    assert(response_str.find("Home page") != std::string::npos);
    
    std::cout << "test_basic_routing passed\n";
}

void test_404_not_found() {
    Router router;
    
    router.add_route("GET", "/exists", [](const HttpRequest& req) {
        return HttpResponse::Builder()
            .status_code(200)
            .body("Found")
            .build();
    });
    
    // Request a route that doesn't exist
    std::string raw_request = "GET /nonexistent HTTP/1.1\r\nHost: localhost\r\n\r\n";
    HttpRequest request(raw_request);
    
    HttpResponse response = router.route(request);
    std::string response_str = response.to_string();
    
    assert(response_str.find("404") != std::string::npos);
    
    std::cout << "test_404_not_found passed\n";
}

void test_different_methods() {
    Router router;
    
    router.add_route("GET", "/users", [](const HttpRequest& req) {
        return HttpResponse::Builder()
            .status_code(200)
            .body("GET users")
            .build();
    });
    
    router.add_route("POST", "/users", [](const HttpRequest& req) {
        return HttpResponse::Builder()
            .status_code(201)
            .body("POST users")
            .build();
    });
    
    // Test GET
    std::string get_request = "GET /users HTTP/1.1\r\nHost: localhost\r\n\r\n";
    HttpRequest req1(get_request);
    HttpResponse resp1 = router.route(req1);
    assert(resp1.to_string().find("200") != std::string::npos);
    assert(resp1.to_string().find("GET users") != std::string::npos);
    
    // Test POST
    std::string post_request = "POST /users HTTP/1.1\r\nHost: localhost\r\n\r\n";
    HttpRequest req2(post_request);
    HttpResponse resp2 = router.route(req2);
    assert(resp2.to_string().find("201") != std::string::npos);
    assert(resp2.to_string().find("POST users") != std::string::npos);
    
    std::cout << "test_different_methods passed\n";
}

auto main() -> int {
    std::cout << "Running tests...\n\n";
    
    try {
        test_basic_routing();
        test_404_not_found();
        test_different_methods();
        
        std::cout << "\nAll tests passed!\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\nTest failed: " << e.what() << "\n";
        return 1;
    }
}