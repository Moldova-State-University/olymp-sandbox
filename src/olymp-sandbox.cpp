#include "definitions.hpp"
#include "config.hpp"
#include "result_info.hpp"
#include "process_manager.hpp"

#include <iostream>

int main(int argc, char **argv)
{
    mc::logger logger = mc::logger::STDOUT();
    logger.info(std::string("start ") + argv[0] + " ...");
    mc::config config;

    if (argc == 1 || !config.init(argc, argv))
    {
        print_usage(argv[0]);
        return 0;
    }
    logger.info(std::string("config.application: " + config.application));
    logger.info(std::string("config.time: ") + std::to_string(config.time_limit));
    logger.info(std::string("config.memory: ") + std::to_string(config.memory_limit));
    logger.info(std::string("config.input: " + config.input));
    logger.info(std::string("config.output: " + config.output));

    try
    {
        mc::process_manager manager(config);
        logger.info("start app");
        mc::result_info result = manager.start_app();

        std::cout << result.JSON() << std::endl;
    }
    catch (const std::exception &e)
    {
        logger.error(e.what());
    }
    logger.info("end job");
    return 0;
}