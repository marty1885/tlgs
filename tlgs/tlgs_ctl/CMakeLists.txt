add_executable(tlgs_ctl main.cpp)
target_link_libraries(tlgs_ctl PRIVATE Drogon::Drogon)
install(TARGETS tlgs_ctl RUNTIME DESTINATION bin)