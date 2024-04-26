cmake_minimum_required(VERSION 3.13)
project(LoneDefender)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Add the executable
add_executable(LoneDefender ${SRC_DIR}/main.cpp)

add_subdirectory(${SRC_DIR}/game)
add_subdirectory(${SRC_DIR}/player)
add_subdirectory(${SRC_DIR}/animation)
add_subdirectory(${SRC_DIR}/enemy)

target_include_directories(LoneDefender PRIVATE 
"${INCLUDE_DIR}"
"${INCLUDE_DIR}/game"
"${INCLUDE_DIR}/player"
"${INCLUDE_DIR}/animation"
"${INCLDUE_DIR}/enemy")   

# Link SFML libraries to the executable
target_link_libraries(LoneDefender PRIVATE sfml-graphics sfml-window sfml-system)