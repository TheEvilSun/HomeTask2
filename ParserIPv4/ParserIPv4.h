#pragma once
#include <vector>
#include "Address.h"

namespace IPv4 {
std::vector<Address> parse(const std::string& file);
}
