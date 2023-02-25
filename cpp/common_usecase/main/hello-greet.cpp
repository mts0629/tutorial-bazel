#include "hello-greet.hpp"

#include <string>

#include "constants.hpp"

std::string get_greet(const std::string &who) {
    return constants::PREFIX + who;
}
