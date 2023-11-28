#pragma once

#include <string>
#include <tuple>

namespace IPv4 {
class Address {
    uint32_t m_address = 0;
    bool m_valid = false;

public:
    Address(){}
    Address(uint32_t address);
    Address(const std::string& address);
    Address(const std::tuple<int, int, int, int>& address);
    Address(std::initializer_list<int> address);

    bool isValid() const;

    int firstByte() const;
    int secondByte() const;
    int thirdByte() const;
    int fourthByte() const;

    std::string toString() const;
    int64_t toInt() const;
    std::tuple<int, int, int, int> toTuple() const;

    static bool isValidString(const std::string& address);

    bool operator==(const Address& rhv) const;
    bool operator!=(const Address& rhv) const;
};
}
