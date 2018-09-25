#include <iostream>
#include <luna/luna.h>
#include "docopt/docopt.h"

static const std::string version{"1.0.3"};
static const std::string pandia{"pandia"};

void error_logger(luna::log_level level, const std::string &message)
{
    switch (level)
    {
//        case luna::log_level::DEBUG:
//            std::cerr << "[  DEBUG] " << message << std::endl;
//            break;
        case luna::log_level::INFO:
            std::cerr << "[   INFO] " << message << std::endl;
            break;
        case luna::log_level::WARNING:
            std::cerr << "[WARNING] " << message << std::endl;
            break;
        case luna::log_level::ERROR:
            std::cerr << "[  ERROR] " << message << std::endl;
            break;
        case luna::log_level::FATAL:
            std::cerr << "[  FATAL] " << message << std::endl;
            break;
    }
}

void access_logger(const luna::request &request, const luna::response &response)
{
    std::cout << request.ip_address << ": " << luna::to_string(request.method) << " [" << response.status_code << "] "
              << request.path << " " << request.http_version << " "
              << (request.headers.count("user-agent") ? request.headers.at("user-agent") : "[no user-agent]") << " { "
              << std::chrono::duration_cast<std::chrono::microseconds>(request.end - request.start).count() << "us } "
              << std::endl;
}

int main(int argc, char **argv)
{
    static const char USAGE[] =
            R"(pandia.

    Usage:
      pandia [options] [<path_to_serve>]
      pandia (-h | --help)
      pandia --version

    Options:
      -h --help     Show this screen.
      --version     Show version.
      -p <port> --port <port>           The port to run from. [default: 8273]
      path_to_serve Optional path to serve file from. [default: ./]
    )";

    std::string path;
    uint16_t port;

    std::map<std::string, docopt::value> args
            = docopt::docopt(USAGE,
                             {argv + 1, argv + argc},
                             true,               // show help if requested
                             pandia + " " + version);  // version string

    for (auto const &arg : args)
    {
        if ((arg.first == "<path_to_serve>") && (arg.second.isString()))
        {
            path = arg.second.asString();
        }
        if (arg.first == "--port")
        {
            port = arg.second.asLong();
        }
    }

    std::string name{"Pandia"};
    std::cout << "============\n" << name << " " << version << "\n============\n" << std::endl;

    luna::set_error_logger(error_logger);
    luna::set_access_logger(access_logger);

    error_logger(luna::log_level::INFO, "Serving files from `" + path + "`");

    luna::server server{luna::server::server_identifier_and_version{name, version}};

    auto router = server.create_router("/");

    router->serve_files("/", path);


    server.start(port);

    return 0;
}
