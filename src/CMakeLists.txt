cmake_minimum_required(VERSION 2.6)

add_executable(
welterd
api.cpp
main.cpp
notification.cpp
logger.cpp
util.cpp
profile.cpp
)

target_link_libraries(
welterd
notify
gtk-3
gio-2.0
jsoncpp
curl
)

install(TARGETS welterd RUNTIME DESTINATION bin)
