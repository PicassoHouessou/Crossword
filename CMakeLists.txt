cmake_minimum_required(VERSION 3.0)

project(MyProject)

# Define source and header directories
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Define tests directory
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Define assets directory
set(ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)


# Find all source files
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.c")

# Find all header files
file(GLOB_RECURSE HEADERS "${INCLUDE_DIR}/*.h")

# Create the executable
add_executable(crossword ${SOURCES} ${HEADERS})

# Specify include directories
target_include_directories(crossword PRIVATE ${INCLUDE_DIR})

# Copy the assets directory to the build directory
file(COPY ${ASSETS_DIR} DESTINATION ${CMAKE_BINARY_DIR})
