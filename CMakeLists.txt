cmake_minimum_required(VERSION 2.8.7)

include_directories(include)
file(GLOB LIB_SOURCES "server.c" "src/*.c" "include/*.h")

project (server)
add_executable(${CMAKE_PROJECT_NAME} ${LIB_SOURCES})
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY C_STANDARD 99)
target_link_libraries(${CMAKE_PROJECT_NAME} progbase jansson ssl)
#add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>)

project (tcpclient)
add_executable(${CMAKE_PROJECT_NAME} "client.c")
target_link_libraries(${CMAKE_PROJECT_NAME} progbase ssl)

SET(CMAKE_C_FLAGS "-std=c99 -Werror -Wall")