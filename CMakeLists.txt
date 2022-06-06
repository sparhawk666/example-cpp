cmake_minimum_required(VERSION 3.14)

project(cpp-plant-waterer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SPDLOG_VERSION v1.10.0)

option(CodeCoverage "CodeCoverage" OFF)
option(CPP_PLANT_WATERER_TESTS "Build the tests" ON)

# Enforce the use of new LTO compatibility, this add support for all compilers known to CMake
cmake_policy(SET CMP0069 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)

include(CheckIPOSupported)
check_ipo_supported(RESULT ltosupported OUTPUT error)

if( ltosupported )
  message(STATUS "IPO / LTO enabled for RELEASE")
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
else()
  message(STATUS "IPO / LTO not supported: <${error}>")
endif()

# Configure CCache if available
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

if(CPP_PLANT_WATERER_TESTS)
  include(CTest)
  if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/")
#    include(CodeCoverage)
#    append_coverage_compiler_flags()
#    setup_target_for_coverage_lcov(NAME coverage EXECUTABLE ${CMAKE_PROJECT_NAME}_tst DEPENDENCIES ${CMAKE_PROJECT_NAME}_tst BASE_DIRECTORY "${PROJECT_SOURCE_DIR}" EXCLUDE "lib/*" "../iothub-software-hsm/*" "build/*" "tst/*" "/usr/*" "../build-iothub-Desktop-Debug/*" "CMakeCCompilerId.c")
  endif()
endif()

# Function to link library as system library, this will skip compiler warnings
function(target_link_libraries_system target)
  set(libs ${ARGN})
  foreach(lib ${libs})
    get_target_property(lib_include_dirs ${lib} INTERFACE_INCLUDE_DIRECTORIES)
    target_include_directories(${target} SYSTEM PRIVATE ${lib_include_dirs})
    target_link_libraries(${target} PRIVATE ${lib})
  endforeach(lib)
endfunction(target_link_libraries_system)

# Add plugin source code
add_subdirectory(src)
add_subdirectory(app)

# Add unit testing if build option is enabled
if(CPP_PLANT_WATERER_TESTS)
  # Download and unpack googletest at configure time
  configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
  execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
  if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
  endif()
  execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
  if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
  endif()

  # Prevent overriding the parent project's compiler/linker
  # settings on Windows
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  # Add googletest directly to our build. This defines
  # the gtest and gtest_main targets.
  add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                  ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                  EXCLUDE_FROM_ALL)

  # Add plugin test code
  add_subdirectory(tst)
endif()
