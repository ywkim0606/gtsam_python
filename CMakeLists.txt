# This file should be used as a template for creating new projects with Python
# wrapping using the CMake tools

# ##############################################################################
# * 1. To create your own project, replace "gtsam_planner" with the actual name
#   of your project
cmake_minimum_required(VERSION 3.9)
project(gtsam_planner CXX C)
set(CXX_STANDARD 11)

# ##############################################################################
# * 2. Find GTSAM components so we have access to the GTSAM Cython install path
find_package(GTSAM REQUIRED) # Uses installed package
# Note: Since Jan-2019, GTSAMConfig.cmake defines exported CMake targets that
# automatically do include the include_directories() without the need to call
# include_directories(), just target_link_libraries(NAME gtsam)

# ##############################################################################
# * 3. Add the local source directory for CMake Ensure that local folder is
#   searched before library folders
include_directories(BEFORE "${PROJECT_SOURCE_DIR}")

# ##############################################################################
# * 4. Build static library from common sources. This is a common cmake step
#   where we load all the source files and link against the GTSAM library.
add_library(${PROJECT_NAME} SHARED cpp/planning/SingleValueConstraint.h cpp/planning/SingleValueConstraint.cpp
                                   cpp/planning/MultiValueConstraint.h cpp/planning/MultiValueConstraint.cpp
                                   cpp/planning/NotSingleValueConstraint.h cpp/planning/NotSingleValueConstraint.cpp
                                   cpp/planning/OrConstraint.h cpp/planning/OrConstraint.cpp
                                   cpp/planning/MutexConstraint.h cpp/planning/MutexConstraint.cpp
                                   cpp/planning/BinarySameConstraint.h cpp/planning/BinarySameConstraint.cpp
                                   cpp/planning/NullConstraint.h cpp/planning/NullConstraint.cpp
                                   cpp/planning/OperatorOrConstraint.h cpp/planning/OperatorOrConstraint.cpp
                                   cpp/planning/FrameConstraint.h cpp/planning/FrameConstraint.cpp)
target_link_libraries(${PROJECT_NAME} gtsam)

# ##############################################################################
# * 5. Install library
install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin)

# ##############################################################################
# # Build tests (CMake tracks the dependecy to link with GTSAM through our
# project's static library) gtsamAddTestsGlob("${PROJECT_NAME}"
# "tests/test*.cpp" "" "${PROJECT_NAME}")

# add_subdirectory(cpp/planning/tests)

# ##############################################################################
# # Build scripts (CMake tracks the dependecy to link with GTSAM through our
# project's static library) gtsamAddExamplesGlob("*.cpp" "" "${PROJECT_NAME}")

# ##############################################################################
# Upto this point, we've only focused on building the C++ library. For details
# on how to build the python wrapper, please see the CMakeLists.txt file in the
# `python` directory.
add_subdirectory(python)
