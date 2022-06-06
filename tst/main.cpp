#include "gtest/gtest.h"
#include <spdlog/spdlog.h>

int main(int argc, char **argv)
{
    spdlog::flush_on(spdlog::level::debug);
    spdlog::set_level(spdlog::level::trace);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
