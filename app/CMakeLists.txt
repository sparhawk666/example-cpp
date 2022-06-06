set(SOURCES
  main.cpp
)

set(LINK_LIBRARIES_PRIVATE
    spdlog::spdlog_header_only
)

set(LINK_LIBRARIES
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(PLUGIN_COMPILE_OPTIONS -Werror -pedantic-errors -Wall -Wextra -Wsign-conversion -Wstrict-aliasing -pedantic -Wunreachable-code -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-include-dirs -Woverloaded-virtual -Wredundant-decls -Wshadow -Wstrict-overflow=5 -Wswitch-default -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(PLUGIN_COMPILE_OPTIONS -Werror -pedantic-errors -Wall -Wextra -Wsign-conversion -Wstrict-aliasing -pedantic -Wunreachable-code -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wshadow -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option)
endif()

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
target_link_libraries_system(${CMAKE_PROJECT_NAME} ${LINK_LIBRARIES_PRIVATE})
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_PROJECT_NAME}_lib ${LINK_LIBRARIES})
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC ${PLUGIN_COMPILE_OPTIONS})

install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION bin)