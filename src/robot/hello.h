#ifndef ROBOT_HELLO_H
#define ROBOT_HELLO_H

#include <string_view>

namespace robot {

constexpr std::string_view say_hello() {
  return "Hello World!";
}

} // namespace robot

#endif
