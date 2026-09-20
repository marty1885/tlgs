add_executable(tlgs_ctl main.cpp)
target_link_libraries(tlgs_ctl PRIVATE Drogon::Drogon tlgsutils)
install(TARGETS tlgs_ctl RUNTIME DESTINATION bin)
target_compile_features(tlgs_ctl PRIVATE cxx_std_20)
