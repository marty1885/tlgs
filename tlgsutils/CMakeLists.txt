find_package(toml11 REQUIRED)
find_package(fmt REQUIRED)
find_package(ICU REQUIRED COMPONENTS uc)
add_library(tlgsutils ranking/features.cpp gemini_parser.cpp robots_txt_parser.cpp site_identity.cpp tarpit.cpp url_parser.cpp utils.cpp)
target_link_libraries(tlgsutils PUBLIC Drogon::Drogon dremini xxhash toml11::toml11)
target_link_libraries(tlgsutils PRIVATE fmt::fmt libtarpit::tarpit ICU::uc)
target_compile_features(tlgsutils PRIVATE cxx_std_20)

if(TLGS_BUILD_TESTS)
    add_executable(tlgsutils_test tests/main.cpp
        tests/ranking_features_test.cpp
        tests/gemini_parser_test.cpp
        tests/robots_txt_parser_test.cpp
        tests/site_identity_test.cpp
        tests/url_parser_test.cpp
        tests/utils_test.cpp
        tests/url_blacklist_test.cpp)
    target_link_libraries(tlgsutils_test Drogon::Drogon tlgsutils)
    target_include_directories(tlgsutils_test PRIVATE .)
    target_precompile_headers(tlgsutils_test PRIVATE tests/pch.hpp)
    ParseAndAddDrogonTests(tlgsutils_test)
endif()
