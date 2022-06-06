#include <spdlog/spdlog.h>

#include <memory>
#include <spdlog/sinks/stdout_color_sinks.h>

int main(int argc, char* argv[])
{
    auto logLevel = spdlog::level::debug;
    spdlog::set_level(logLevel);

    spdlog::debug("Main is on 🚀");

    return 0;
}
