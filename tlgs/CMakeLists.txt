add_subdirectory(crawler)
add_subdirectory(server)
add_subdirectory(tlgs_ctl)

install(FILES config.json server_config.json site_identity_rules.toml DESTINATION /etc/tlgs/)
