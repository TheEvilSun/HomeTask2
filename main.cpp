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

        using SortVector = std::vector<std::reference_wrapper<IPv4::Address>>;
        SortVector sortedIp(ips.begin(), ips.end());
        std::sort(sortedIp.begin(), sortedIp.end(), [](const auto& ip1, const auto& ip2){
            return ip1.get().toInt() > ip2.get().toInt();
        });

        SortVector sortedFirst1;
        std::remove_copy_if(sortedIp.begin(), sortedIp.end(), std::back_inserter(sortedFirst1), [](const auto& ip){
                               auto firstByte = ip.get().firstByte();
                               return !(firstByte == 1);
                           }), sortedFirst1.end();

        SortVector sortedFirst46Second70;
        std::remove_copy_if(sortedIp.begin(), sortedIp.end(), std::back_inserter(sortedFirst46Second70), [](const auto& ip){
                                        auto firstByte = ip.get().firstByte();
                                        auto secondByte = ip.get().secondByte();
                                        return !(firstByte == 46 && secondByte == 70);
                                    }), sortedFirst46Second70.end();

        SortVector sortedAny46;
        std::remove_copy_if(sortedIp.begin(), sortedIp.end(), std::back_inserter(sortedAny46), [](const auto& ip){
                                        auto firstByte = ip.get().firstByte();
                                        auto secondByte = ip.get().secondByte();
                                        auto thirdByte = ip.get().thirdByte();
                                        auto fourthByte = ip.get().fourthByte();
                                        return !(firstByte == 46 || secondByte == 46 || thirdByte == 46 || fourthByte == 46);
                                    }), sortedAny46.end();

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
