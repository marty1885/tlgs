add_executable(tlgs_server
  main.cpp
  controllers/search.cpp
  controllers/tools.cpp
  controllers/api.cpp)
find_package(Drogon REQUIRED)
find_package(fmt REQUIRED)
target_link_libraries(tlgs_server PRIVATE Drogon::Drogon dremini tlgsutils fmt::fmt)
target_include_directories(tlgs_server PRIVATE .)
drogon_create_views(tlgs_server ${CMAKE_CURRENT_SOURCE_DIR}/templates
                    ${CMAKE_CURRENT_BINARY_DIR})
target_precompile_headers(tlgs_server PRIVATE pch.h)
add_custom_command(
  TARGET tlgs_server POST_BUILD
  COMMAND ${CMAKE_COMMAND}
          -E
          copy_directory
          ${CMAKE_CURRENT_SOURCE_DIR}/contents
          $<TARGET_FILE_DIR:tlgs_server>/contents)

install(TARGETS tlgs_server RUNTIME DESTINATION bin)