# ============================================================================
# http-server-cpp — CMake Build System
# ============================================================================
cmake_minimum_required(VERSION 3.16)

project(http-server-cpp
    VERSION   1.0.0
    LANGUAGES CXX
    DESCRIPTION "A lightweight HTTP server written in C++ using raw sockets"
)

# ── Global compiler settings ────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)            # use -std=c++17, not -std=gnu++17

# Put all binaries in a predictable location
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ── Compiler warnings (applied to every target below) ───────────────────────
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
    -Wsign-conversion
)

# ── Build-type-specific flags ───────────────────────────────────────────────
# Debug   → sanitizers + full debug info
# Release → optimised, no debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g -O0 -fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O2 -DNDEBUG)
endif()

# ── Targets ─────────────────────────────────────────────────────────────────

# 1. Socket server
add_executable(socket_server src/socket.cpp)

# 2. Socket client
add_executable(socket_client src/client.cpp)

# ── Platform-specific link libraries ────────────────────────────────────────
# On Linux/macOS POSIX sockets are part of libc — nothing extra is needed.
# On Windows (MinGW / MSVC) we must link ws2_32.
if(WIN32)
    target_link_libraries(socket_server PRIVATE ws2_32)
    target_link_libraries(socket_client PRIVATE ws2_32)
endif()

# ── Install rules (optional, for `cmake --install`) ────────────────────────
install(TARGETS socket_server socket_client
    RUNTIME DESTINATION bin
)

# ── Summary message ─────────────────────────────────────────────────────────
message(STATUS "")
message(STATUS "╔══════════════════════════════════════════════════════════╗")
message(STATUS "║  http-server-cpp v${PROJECT_VERSION}                              ║")
message(STATUS "║  Build type : ${CMAKE_BUILD_TYPE}                               ║")
message(STATUS "║  Compiler   : ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}                          ║")
message(STATUS "║  C++ std    : ${CMAKE_CXX_STANDARD}                                    ║")
message(STATUS "╚══════════════════════════════════════════════════════════╝")
message(STATUS "")
