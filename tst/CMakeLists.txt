set(BINARY ${CMAKE_PROJECT_NAME}_tst)


find_package(Threads REQUIRED)
enable_testing()

set(SOURCES
        main.cpp
)

file(GLOB_RECURSE SOURCES_GLOB CONFIGURE_DEPENDS
        "controllers/*.cpp"
        "controllers/*.h"
)

set(SOURCES_FINAL ${SOURCES_GLOB} ${SOURCES} )


include(GoogleTest)

add_executable(${BINARY} ${SOURCES_FINAL})
gtest_discover_tests(${BINARY} TEST_PREFIX new:)

set(LINK_LIBRARIES
        ${CMAKE_PROJECT_NAME}_lib
        gtest
        gmock
        Threads::Threads
)

target_link_libraries_system(${BINARY} ${LINK_LIBRARIES_PRIVATE})
target_link_libraries(${BINARY} PUBLIC ${LINK_LIBRARIES})