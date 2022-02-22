add_library(tlgsutils gemini_parser.cpp robots_txt_parser.cpp url_parser.cpp utils.cpp)
target_link_libraries(tlgsutils PUBLIC Drogon::Drogon dremini xxhash)
target_compile_features(tlgsutils PRIVATE cxx_std_20)

if(TLGS_BUILD_TESTS)
    add_executable(tlgsutils_test tests/main.cpp
        tests/gemini_parser_test.cpp
        tests/robots_txt_parser_test.cpp
        tests/url_parser_test.cpp
        tests/utils_test.cpp
        tests/url_blacklist_test.cpp)
    target_link_libraries(tlgsutils_test Drogon::Drogon tlgsutils)
    target_include_directories(tlgsutils_test PRIVATE .)
    ParseAndAddDrogonTests(tlgsutils_test)
endif()
