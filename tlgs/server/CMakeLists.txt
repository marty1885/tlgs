add_executable(tlgs_server
  main.cpp
  known_security_txt.cpp
  controllers/search.cpp
  controllers/tools.cpp
  controllers/api.cpp
  controllers/decoy.cpp
  controllers/tarpit.cpp)
  target_compile_features(tlgs_server PRIVATE cxx_std_20)
find_package(fmt REQUIRED)
target_link_libraries(tlgs_server PRIVATE Drogon::Drogon dremini tlgsutils fmt::fmt spartoi)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_link_libraries(tlgs_server PRIVATE llunveil)
endif()
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

# The generated header carries the schema checked by ranking/model.cpp.
set(TLGS_RANKER_MODEL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ranking" CACHE PATH "Highway model bundle for learned search ranking")
if(TLGS_RANKER_MODEL_DIR)
  get_filename_component(TLGS_RANKER_DIRECTORY "${TLGS_RANKER_MODEL_DIR}" ABSOLUTE BASE_DIR "${CMAKE_SOURCE_DIR}")
  set(TLGS_RANKER_SOURCE "${TLGS_RANKER_DIRECTORY}/ranker.cc")
  find_package(hwy CONFIG REQUIRED)
  target_sources(tlgs_server PRIVATE ranking/model.cpp "${TLGS_RANKER_SOURCE}")
  target_link_libraries(tlgs_server PRIVATE hwy::hwy)
  target_compile_definitions(tlgs_server PRIVATE TLGS_ENABLE_LEARNED_RANKING=1)
  set_source_files_properties(ranking/model.cpp PROPERTIES
    INCLUDE_DIRECTORIES "${TLGS_RANKER_DIRECTORY}")
  set_source_files_properties("${TLGS_RANKER_SOURCE}" PROPERTIES
    INCLUDE_DIRECTORIES "${TLGS_RANKER_DIRECTORY}"
    SKIP_PRECOMPILE_HEADERS ON COMPILE_OPTIONS "-fno-fast-math;-ffp-contract=off")
  message(STATUS "TLGS learned ranking model: ${TLGS_RANKER_DIRECTORY}")
endif()
