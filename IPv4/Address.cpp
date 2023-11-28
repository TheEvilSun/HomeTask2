#include "Address.h"
#include <sstream>

namespace IPv4 {

Address::Address(uint32_t address) : m_address(address), m_valid(true) {
}

Address::Address(const std::string &address) {
    if(address.empty()) {
        m_valid = false;
        return;
    }

    std::istringstream stream(address);
    int ip_i = 3;
    for(std::string byte; std::getline(stream, byte, '.');) {
        if(byte.empty() || ip_i < 0) {
            m_valid = false;
            return;
        }

        int byteInt;
        try{
            byteInt = std::stoi(byte);
        }
        catch(std::invalid_argument const& ex) {
            m_valid = false;
            return;
        }

        if((byteInt < 0) || (byteInt > 255)) {
            m_valid = false;
            return;
        }

        m_address = m_address | (byteInt << ip_i * 8);
        ip_i--;
    }

    m_valid = ip_i == -1;
}

Address::Address(std::initializer_list<int> address) {
    if(address.size() != 4) {
        m_valid = false;
        return;
    }

    uint8_t ip_i = 3;
    for(auto it = address.begin(); it != address.end(); it++) {
        if((*it < 0) || (*it > 255)) {
            m_valid = false;
            return;
        }

        m_address = m_address | (*it << ip_i * 8);
        ip_i--;
    }

    m_valid = true;
}

Address::Address(const std::tuple<int, int, int, int> &address) {
    uint8_t ip_i = 3;
    int bytes[] = { std::get<0>(address), std::get<1>(address), std::get<2>(address), std::get<3>(address) };

    for(int i = 0; i < 4; i++) {
        if((bytes[i] < 0) || (bytes[i] > 255)) {
            m_valid = false;
            return;
        }

        m_address = m_address | (bytes[i] << ip_i * 8);
        ip_i--;
    }

    m_valid = true;
}

bool Address::isValid() const {
    return m_valid;
}

int Address::firstByte() const {
    if(!m_valid) {
        return -1;
    }

    return m_address >> 24;
}

int Address::secondByte() const {
    if(!m_valid) {
        return -1;
    }

    return (m_address >> 16) & 0x000000ff;
}

int Address::thirdByte() const {
    if(!m_valid) {
        return -1;
    }

    return (m_address >> 8) & 0x000000ff;
}

int Address::fourthByte() const {
    if(!m_valid) {
        return -1;
    }

    return m_address & 0x000000ff;
}

std::string Address::toString() const {
    if(!m_valid) {
        return std::string();
    }

    auto b1 = m_address >> 24;
    auto b2 = (m_address >> 16) & 0x000000ff;
    auto b3 = (m_address >> 8) & 0x000000ff;
    auto b4 = m_address & 0x000000ff;
    return std::to_string(b1) + '.' + std::to_string(b2) + '.' + std::to_string(b3) + '.' + std::to_string(b4);
}

int64_t Address::toInt() const {
    if(!m_valid) {
        return -1;
    }

    return m_address;
}

std::tuple<int, int, int, int> Address::toTuple() const {
    auto b1 = m_address >> 24;
    auto b2 = (m_address >> 16) & 0x000000ff;
    auto b3 = (m_address >> 8) & 0x000000ff;
    auto b4 = m_address & 0x000000ff;
    return std::make_tuple(b1, b2, b3, b4);
}

bool Address::operator==(const Address& rhv) const {
    if(m_valid && rhv.m_valid) {
        return m_address == rhv.m_address;
    }
    return !m_valid && !rhv.m_valid;
}

bool Address::operator!=(const Address& rhv) const {
    if(m_valid && rhv.m_valid) {
        return m_address != rhv.m_address;
    }
    return m_valid != rhv.m_valid;
}

bool Address::isValidString(const std::string& address) {
    if(address.empty()) {
        return false;
    }

    std::istringstream stream(address);
    int ip_i = 3;
    for(std::string byte; std::getline(stream, byte, '.');) {
        if(byte.empty() || ip_i < 0) {
            return false;
        }

        int byteInt;
        try{
            byteInt = std::stoi(byte);
        }
        catch(std::invalid_argument const& ex) {
            return false;
        }

        if((byteInt < 0) || (byteInt > 255)) {
            return false;
        }

        ip_i--;
    }

    return ip_i == -1;
}

}
