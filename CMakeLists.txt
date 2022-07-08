cmake_minimum_required(VERSION 3.10)

# set the project name
project(Tetra)

cmake_minimum_required (VERSION 3.2)

project(cs5625solution LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBS "")
set(DEFS "-DGL_SILENCE_DEPRECATION")
set(INCS "")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# ----------------------------------------------------------------
# Include nanogui as a subproject

# Disable building extras we won't need (pure C++ project)
set(NANOGUI_BUILD_EXAMPLE OFF CACHE BOOL " " FORCE)
set(NANOGUI_BUILD_PYTHON  OFF CACHE BOOL " " FORCE)
set(NANOGUI_INSTALL       OFF CACHE BOOL " " FORCE)

set(NANOGUI_BASE_DIR "ext/nanogui")

# Add the configurations from nanogui
add_subdirectory(${NANOGUI_BASE_DIR})

# For reliability of parallel build, make the NanoGUI targets dependencies
set_property(TARGET glfw glfw_objects nanogui PROPERTY FOLDER "dependencies")

list(APPEND DEFS ${NANOGUI_EXTRA_DEFS})
list(APPEND LIBS nanogui ${NANOGUI_EXTRA_LIBS})
list(APPEND INCS ${NANOGUI_EXTRA_INCS} ${NANOGUI_BASE_DIR}/include)

# ----------------------------------------------------------------
# Create executable targets, one per subdirectory.

# Creates an executable
#   This assumes that the executable's C++ source code is contained in a folder in the same directory as this file.
#   This adds all source files in the given folder to a new executable target with the same name as the directory.
function(createExecutable EXE_NAME)
  set(EXE_INCLUDE_DIR ${EXE_NAME})
  file(GLOB EXE_SRC "${EXE_INCLUDE_DIR}/*[.cpp|.h|.hpp]")
  set(COMMON_INCLUDE_DIR "Common")
  file(GLOB COMMON_SRC "${COMMON_INCLUDE_DIR}/*[.cpp|.h|.hpp]")
  set(EXE_INCS ${INCS})
  list(APPEND EXE_INCS ${EXE_INCLUDE_DIR})
  add_executable(${EXE_NAME} ${EXE_SRC} ${COMMON_SRC})
  target_compile_definitions(${EXE_NAME} PUBLIC ${DEFS})
  target_include_directories(${EXE_NAME} PUBLIC ${EXE_INCS})
  target_link_libraries(${EXE_NAME} ${LIBS})
endfunction(createExecutable)

# Create the targets for all desired executables
# Can comment out ones you are not currently concerned with to save compile time.
createExecutable("Tetra")