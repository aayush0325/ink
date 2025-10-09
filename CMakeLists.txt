cmake_minimum_required(VERSION 3.10)
project(ink)

set(CMAKE_CXX_STANDARD 23)

include_directories(${PROJECT_SOURCE_DIR}/include)

# Exports compile_commands.json for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# STEP 1: Collect all implementation files (excluding main.cpp files)
# This creates a library with shared code that both executables can use
file(GLOB_RECURSE LIB_FILES src/*.cpp)
list(FILTER LIB_FILES EXCLUDE REGEX ".*main\\.cpp$")

# STEP 2: Create a static library from implementation files
# This allows code reuse without duplicate main() functions
add_library(interpretr_lib STATIC ${LIB_FILES})

# STEP 3: Create the main executable
# Links only src/main.cpp + the library
add_executable(main src/main.cpp)
target_link_libraries(main interpretr_lib)

# STEP 4: Collect test files (excluding main.cpp from src/)
file(GLOB_RECURSE TEST_FILES tests/*.cpp)

# STEP 5: Create the test executable  
# Links test files + the library (but NOT src/main.cpp)
add_executable(tests ${TEST_FILES})
target_link_libraries(tests interpretr_lib)
