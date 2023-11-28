cmake_minimum_required(VERSION 3.14)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(HomeTask2 VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(version.h.in version.h)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1
)

FetchContent_MakeAvailable(Catch2)

add_subdirectory(IPv4)
add_subdirectory(ParserIPv4)
add_executable(HomeTask2 main.cpp)
add_executable(IPv4Test IPv4test.cpp)

target_link_libraries(IPv4Test PRIVATE
    Catch2::Catch2WithMain
    IPv4
    ParserIPv4
)
target_include_directories(IPv4Test PUBLIC
    "${PROJECT_SOURCE_DIR}/IPv4"
    "${PROJECT_SOURCE_DIR}/ParserIPv4"
)

target_include_directories(ParserIPv4 PUBLIC
    "${PROJECT_SOURCE_DIR}/IPv4"
)


target_link_libraries(HomeTask2 PUBLIC IPv4 ParserIPv4)
target_link_libraries(ParserIPv4 PUBLIC IPv4)

target_include_directories(HomeTask2 PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/IPv4"
    "${PROJECT_SOURCE_DIR}/ParserIPv4"
)

add_custom_command(
    TARGET ${PROJECT_NAME}  POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${PROJECT_SOURCE_DIR}/ips.txt"
    "${PROJECT_BINARY_DIR}/ips.txt"
)

install(TARGETS HomeTask2 RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT alservol@gmail.com)

include(CPack)

enable_testing()

add_test(IPv4Test IPv4Test)
