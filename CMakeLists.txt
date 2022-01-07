cmake_minimum_required(VERSION 3.15)
project(tlgs)

option(TLGS_BUILD_TESTS "Build TLGS tests" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(DREMINI_BUILD_EXAMPLES OFF)
set(DREMINI_BUILD_TEST OFF)
add_subdirectory(thrid_party/dremini)
include_directories(thrid_party/dremini)

find_package(Drogon REQUIRED)
include_directories(.)
add_subdirectory(tlgsutils)
add_subdirectory(tlgs)

install(FILES systemd/tlgs_crawler.service systemd/tlgs_crawler.timer systemd/tlgs_server.service DESTINATION /etc/systemd/)
install(FILES systemd/tlgs.conf DESTINATION lib/sysuser.d)

include(Package.cmake)