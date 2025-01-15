cmake_minimum_required(VERSION 3.7)

set(APP_NAME archers)

project(${APP_NAME})

set(APP_SOURCE)

file(GLOB_RECURSE APP_SOURCE
    ${CMAKE_SOURCE_DIR}/src/core/*.h
    ${CMAKE_SOURCE_DIR}/src/core/*.cpp
    ${CMAKE_SOURCE_DIR}/utils/*.h
    ${CMAKE_SOURCE_DIR}/utils/*.cpp
    ${CMAKE_SOURCE_DIR}/math/*.h
    ${CMAKE_SOURCE_DIR}/math/*.cpp
    ${CMAKE_SOURCE_DIR}/components/*.h
    ${CMAKE_SOURCE_DIR}/components/*.cpp
    ${CMAKE_SOURCE_DIR}/systems/*.h
    ${CMAKE_SOURCE_DIR}/systems/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.h
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_subdirectory(thirdparty)

add_executable(${APP_NAME}
    ${APP_SOURCE}
)

target_include_directories(${APP_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(${APP_NAME} PRIVATE
    EnTT
    SDL2::SDL2
    SDL2_image
)

set_property(TARGET ${APP_NAME} PROPERTY CXX_STANDARD 17)

file(COPY "${CMAKE_SOURCE_DIR}/assets" DESTINATION "${CMAKE_BINARY_DIR}")