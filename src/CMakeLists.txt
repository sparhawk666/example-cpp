set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "controllers/*.cpp"
        "controllers/*.h"
)

set(LINK_LIBRARIES
)

set(LINK_LIBRARIES_PRIVATE
        spdlog::spdlog_header_only
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(PLUGIN_COMPILE_OPTIONS -pedantic-errors -Wall -Wextra -Wsign-conversion -Wstrict-aliasing -pedantic -Wunreachable-code -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-include-dirs -Woverloaded-virtual -Wredundant-decls -Wshadow -Wstrict-overflow=5 -Wswitch-default -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(PLUGIN_COMPILE_OPTIONS -pedantic-errors -Wall -Wextra -Wsign-conversion -Wstrict-aliasing -pedantic -Wunreachable-code -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wshadow -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option)
endif()


# Export src as library for app and unit testing
add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME}_lib PUBLIC ${LINK_LIBRARIES})
target_link_libraries_system(${CMAKE_PROJECT_NAME}_lib ${LINK_LIBRARIES_PRIVATE})
target_include_directories(${CMAKE_PROJECT_NAME}_lib INTERFACE PUBLIC .)
target_compile_options(${CMAKE_PROJECT_NAME}_lib PUBLIC ${PLUGIN_COMPILE_OPTIONS})
