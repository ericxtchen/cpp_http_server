install(
    TARGETS cpp_http_server_exe
    RUNTIME COMPONENT cpp_http_server_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
