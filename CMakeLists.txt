cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    cpp_http_server
    VERSION 0.1.0
    DESCRIPTION "http server to learn cpp"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    cpp_http_server_lib OBJECT
    source/lib.cpp
    source/HttpRequest.cpp
    source/socket_wrappers/server_raii.cpp
    source/socket_wrappers/client_raii.cpp
    source/HttpResponse.cpp
)

target_include_directories(
    cpp_http_server_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(cpp_http_server_lib PUBLIC cxx_std_20)

# ---- Declare executable ----

add_executable(cpp_http_server_exe source/main.cpp)
add_executable(cpp_http_server::exe ALIAS cpp_http_server_exe)

set_property(TARGET cpp_http_server_exe PROPERTY OUTPUT_NAME cpp_http_server)

target_compile_features(cpp_http_server_exe PRIVATE cxx_std_20)

target_link_libraries(cpp_http_server_exe PRIVATE cpp_http_server_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT cpp_http_server_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of cpp_http_server"
  )
endif()

include(cmake/dev-mode.cmake)
