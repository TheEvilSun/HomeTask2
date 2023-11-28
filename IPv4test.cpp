#include <catch2/catch_test_macros.hpp>
#include "Address.h"
#include "ParserIPv4.h"

TEST_CASE("IPv4 address test") {
    auto add1 = IPv4::Address(0xc2f21252);
    auto add2 = IPv4::Address(std::string("192.168.0.1"));
    auto add3 = IPv4::Address{255, 78, 0, 69};
    auto add4 = IPv4::Address(std::make_tuple(10, 78, 100, 89));
    auto add5 = IPv4::Address(std::string("100.168.0.10.158.29"));
    auto add6 = IPv4::Address({255, 78, 0, -25});
    auto add7 = IPv4::Address(std::make_tuple(10, -7, 100, 89));
    auto add8 = add3;

    REQUIRE(add1.toString() == std::string("194.242.18.82"));
    REQUIRE(add2.firstByte() == 192);
    REQUIRE(add2.secondByte() == 168);
    REQUIRE(add2.thirdByte() == 0);
    REQUIRE(add2.fourthByte() == 1);
    REQUIRE(add3.toString() == std::string("255.78.0.69"));
    REQUIRE(add4.toString() == std::string("10.78.100.89"));
    REQUIRE(add5.isValid() == false);
    REQUIRE(add6.isValid() == false);
    REQUIRE(add7.isValid() == false);
    REQUIRE((add8 == add3) == true);
    REQUIRE((add8 == add2) == false);
    REQUIRE((add8 == add6) == false);
    REQUIRE((add6 == add7) == true);
    REQUIRE(IPv4::Address::isValidString("255.78.0.69") == true);
    REQUIRE(IPv4::Address::isValidString("255..0.69") == false);
    REQUIRE(IPv4::Address::isValidString("255.0.69") == false);
    REQUIRE(IPv4::Address::isValidString("255fgjdf") == false);
    REQUIRE(IPv4::Address::isValidString("") == false);
}

TEST_CASE("Parser test") {
    auto ips = IPv4::parse("ips.txt");
    REQUIRE(ips.size() == 4);
    REQUIRE(ips[0] == IPv4::Address("192.168.0.10"));
    REQUIRE(ips[1] == IPv4::Address{12, 18, 0, 6});
    REQUIRE(ips[2] == IPv4::Address(std::make_tuple(120, 108, 0, 10)));
    REQUIRE(ips[3] == IPv4::Address(0x7f44280a));
}
