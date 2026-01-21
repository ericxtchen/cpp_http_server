#include "lib.hpp"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "cpp_http_server" ? 0 : 1;
}
