#include "ParserIPv4.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <limits>
#include <sstream>

namespace IPv4 {
std::vector<Address> parse(const std::string& file) {
    std::vector<Address> ips;
    auto deleter = [](std::ifstream* file){
        file->close();
        delete file;
    };

    std::unique_ptr<std::ifstream, decltype(deleter)> ipFile(new std::ifstream(file, std::ios::in), deleter);
    if(!ipFile->is_open()) {
        return ips;
    }

    auto ipCount = 0;
    *ipFile >> ipCount;
    ipFile->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(ipCount <= 0) {
        return ips;
    }

    ips.reserve(ipCount);
    std::string line;
    while(std::getline(*ipFile, line)) {
        std::istringstream stream(line);
        while(!stream.eof()) {
            std::string tmp;
            stream >> tmp;
            auto address = Address(tmp);
            if(address.isValid()) {
                ips.push_back(std::move(address));
                break;
            }
        }
    }

    return ips;
}

}
