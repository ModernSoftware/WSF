#include "../Shared.hpp"
#include "../Config.hpp"
#include "boost/program_options.hpp"

#ifndef _CLI_UTILITY_H_
#define _CLI_UTILITY_H_ 1

namespace wsf { namespace cli {

    /*
    * @function parse
    * Parse the command line options when starting a web service
    *
    * @argument|int argc
    * The amount of arguments passed in the command line
    *
    * @argument|char argv
    * The physical string input from the command line
    *
    * @returns bool
    * Returns whether or not the parsing of the command line was successful
    */
    bool parse(int argc, char** argv) {
        namespace opt = boost::program_options;
        opt::options_description description("The C++ Web Service Framework for modern web services");

        description
            .add_options()
            ("help", "print help message")
            ("host,h", opt::value<std::string>(&wsf::config::host), "specify host to listen on (default is http://0.0.0.0)")
            ("port,p", opt::value<std::string>(&wsf::config::port), "specify port to listen on (default is 3000)")
            ("cors,c", opt::value<std::string>(&wsf::config::cors), "specify CORS (default is * which is sometimes unsafe)")
            ("mongo", opt::value<std::string>(&wsf::config::mongo), "MongoDB url (default is mongodb://localhost:27017)")
            ("mongodb", opt::value<std::string>(&wsf::config::mongodb), "MongoDB DB name (default is wsf)")
            ("redis", opt::value<std::string>(&wsf::config::redis), "Redis url (default is localhost)")
            ("redisPort", opt::value<int>(&wsf::config::redisPort), "Redis port (default is 6379)")
            ("redisTimeout", opt::value<int>(&wsf::config::redisTimeout), "Redis timeout (default is 3 in s)");

        opt::variables_map vm;

        try {
            opt::store(opt::parse_command_line(argc, argv, description), vm);

            if (vm.count("help")) {
                std::cout << description << std::endl;
                return true;
            }

            // Update Web Service Config Variables
            if (vm.count("host")) wsf::config::host = vm["host"].as<std::string>();
            if (vm.count("port")) wsf::config::port = vm["port"].as<std::string>();
            if (vm.count("cors")) wsf::config::cors = vm["cors"].as<std::string>();

            // Update Mongo Driver Config Variables
            if (vm.count("mongo")) wsf::config::mongo = vm["mongo"].as<std::string>();
            if (vm.count("mongodb")) wsf::config::mongo = vm["mongodb"].as<std::string>();

            // Update Redis Driver Config Variables
            if (vm.count("redis")) wsf::config::redis = vm["redis"].as<std::string>();
            if (vm.count("redisPort")) wsf::config::redisPort = vm["redisPort"].as<int>();
            if (vm.count("redisTimeout")) wsf::config::redisTimeout = vm["redisTimeout"].as<int>();

        } catch (opt::error& e) {
            std::cerr << e.what() << std::endl;
            return false;
        }

        return true;
    }

} }

#endif
