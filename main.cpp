#include <iostream>
#include <luna/luna.h>

static const std::string version{"1.0.1"};

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
    std::string name{"Pandia"};
    std::cout << "============\n" << name << " " << version << "\n============\n" << std::endl;


    std::string path{"./"};
    if(argc > 1)
        path = argv[1];

    luna::set_error_logger(error_logger);
    luna::set_access_logger(access_logger);

    luna::server server{luna::server::server_identifier_and_version{name, version}};

    auto router = server.create_router("/");

    router->serve_files("/", path);


    server.start(8273);

    return 0;
}