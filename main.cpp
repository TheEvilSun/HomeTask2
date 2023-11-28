#include "Address.h"
#include "ParserIPv4.h"

#include <iostream>
#include <functional>
#include <algorithm>

int main(int argc, char *argv[])
{
    if(argc != 2) {
        std::cout << "Need input file with ip addresses" << std::endl;
    }
    else {
        auto ips = IPv4::parse(argv[1]);

        std::vector<std::reference_wrapper<IPv4::Address>> sortedIp(ips.begin(), ips.end());
        std::sort(sortedIp.begin(), sortedIp.end(), [](const auto& ip1, const auto& ip2){
            return ip1.get().toInt() > ip2.get().toInt();
        });

        auto sortedFirst1 = sortedIp;
        sortedFirst1.erase(std::remove_if(sortedFirst1.begin(), sortedFirst1.end(), [](const auto& ip){
                               auto firstByte = ip.get().firstByte();
                               return !(firstByte == 1);
                           }), sortedFirst1.end());

        auto sortedFirst46Second70 = sortedIp;
        sortedFirst46Second70.erase(std::remove_if(sortedFirst46Second70.begin(), sortedFirst46Second70.end(), [](const auto& ip){
                                        auto firstByte = ip.get().firstByte();
                                        auto secondByte = ip.get().secondByte();
                                        return !(firstByte == 46 && secondByte == 70);
                                    }), sortedFirst46Second70.end());

        auto sortedAny46 = sortedIp;
        sortedAny46.erase(std::remove_if(sortedAny46.begin(), sortedAny46.end(), [](const auto& ip){
                                        auto firstByte = ip.get().firstByte();
                                        auto secondByte = ip.get().secondByte();
                                        auto thirdByte = ip.get().thirdByte();
                                        auto fourthByte = ip.get().fourthByte();
                                        return !(firstByte == 46 || secondByte == 46 || thirdByte == 46 || fourthByte == 46);
                                    }), sortedAny46.end());

        for(const auto& ip : sortedIp) {
            std::cout << ip.get().toString() << std::endl;
        }

        for(const auto& ip : sortedFirst1) {
            std::cout << ip.get().toString() << std::endl;
        }

        for(const auto& ip : sortedFirst46Second70) {
            std::cout << ip.get().toString() << std::endl;
        }

        for(const auto& ip : sortedAny46) {
            std::cout << ip.get().toString() << std::endl;
        }
    }
    return 0;
}
