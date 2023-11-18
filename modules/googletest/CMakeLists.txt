if(CONFIG_GOOGLETEST)

cmake_minimum_required(VERSION 3.13.1)

set(CMAKE_C_FLAGS -m32)
set(CMAKE_CXX_FLAGS -m32)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main
)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

endif()
