add_subdirectory(crawler)
add_subdirectory(server)
add_subdirectory(tlgs_ctl)

install(FILES config.json server_config.json DESTINATION /etc/tlgs/)