cmake_minimum_required(VERSION 3.15)
project(tlgs)

include(GNUInstallDirs)

option(TLGS_BUILD_TESTS "Build TLGS tests" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# include(CheckCXXCompilerFlag)
# check_cxx_compiler_flag("-fstack-protector-strong" HAVE_FSTACK_PROTECTOR)
# if(HAVE_FSTACK_PROTECTOR)
#     message(STATUS "Stack protector enabled")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstack-protector-strong")
# endif()

set(DREMINI_BUILD_EXAMPLES OFF)
set(DREMINI_BUILD_TEST OFF)
set(SPARTOI_BUILD_EXAMPLES OFF)

# Enable tail call optimization so coroutines doesn't blow up the stack
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -foptimize-sibling-calls")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_subdirectory(thrid_party/landlock-unveil)
    include_directories(thrid_party/landlock-unveil)
endif()
add_subdirectory(thrid_party/dremini)
include_directories(thrid_party/dremini)
add_subdirectory(thrid_party/spartoi)
include_directories(thrid_party/spartoi)

find_package(Drogon REQUIRED)
include_directories(.)
add_subdirectory(tlgsutils)
add_subdirectory(tlgs)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    install(FILES systemd/tlgs_crawler.service systemd/tlgs_crawler.timer systemd/tlgs_server.service DESTINATION /etc/systemd/)
    install(FILES systemd/tlgs.conf DESTINATION lib/sysuser.d)
elseif(CMAKE_SYSTEM_NAME STREQUAL "OpenBSD")
    configure_file(openbsd/tlgs_server.in tlgs_server.rc @ONLY)
    install(PROGRAMS "${CMAKE_CURRENT_BINARY_DIR}/tlgs_server.rc"
            DESTINATION /etc/rc.d
            RENAME tlgs_server)
endif()

include(Package.cmake)
