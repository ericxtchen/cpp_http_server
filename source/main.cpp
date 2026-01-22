#include <iostream>
#include "socket_wrappers/server_raii.hpp"
#include "socket_wrappers/client_raii.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Router.hpp"

constexpr int MAX_REQUEST_SIZE = 1024 * 1024;

void add_routes(Router& router) {
	router.add_route("GET", "/", [](const HttpRequest& request){
		return HttpResponse::Builder()
			.status_code(200)
			.headers("Content-Type", "text/html")
			.body("<h1>Hello World!</h1>")
			.build();
	});
}

auto main() -> int
{
	try {
		ServerSocket server;
		Router router;
		add_routes(router);
		while (true) {
			struct sockaddr_in client_address;
        	socklen_t client_len = sizeof(client_address);
			int client_fd = accept(server.get_fd(), (sockaddr*)&client_address, &client_len);
    		if (client_fd < 0) {
        		std::cerr << "Accept failed\n";
        		continue;
    		}
    		ClientSocket client(client_fd);

			std::string request;
			char buffer[4096];
			while (request.size() < MAX_REQUEST_SIZE) {
				ssize_t bytes_read = recv(client.get_fd(), buffer, sizeof(buffer), 0);
				if (bytes_read <= 0) break;
				request.append(buffer, bytes_read);
				if (request.find("\r\n\r\n") != std::string::npos) {
					break;
				}
			}

			if (request.size() >= MAX_REQUEST_SIZE) {
				const char *response = "HTTP/1.1 413 Payload Too Large\r\n\r\n";
				send(client.get_fd(), response, sizeof(response), 0);
			}
			
			HttpRequest http_request(request);
			HttpResponse response = router.route(http_request);
			std::string response_str = response.to_string();
			send(client.get_fd(), response_str.c_str(), response_str.size(), 0);
		}

	} catch (const std::exception& e) {
    	std::cerr << "Server failed: " << e.what() << "\n";
	}
}
