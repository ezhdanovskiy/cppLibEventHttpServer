#include "HttpServer.h"

#include <memory>
#include <cstdint>
#include <iostream>
#include <evhttp.h>
#include <iomanip>
#include <ctime>
#include <sstream>

std::string strtime02()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 80 ,"%d-%m-%Y %I:%M:%S", timeinfo);

    return buffer;
}

int runHttpServer() {
    std::cout << __func__ << " start" << std::endl;

    if (!event_init()) {
        std::cerr << "Failed to init libevent." << std::endl;
        return -1;
    }

    char const SrvAddress[] = "127.0.0.1";
    std::uint16_t SrvPort = 5555;
    std::unique_ptr<evhttp, decltype(&evhttp_free)> Server(evhttp_start(SrvAddress, SrvPort), &evhttp_free);
    if (!Server) {
        std::cerr << "Failed to init http server." << std::endl;
        return -1;
    }
    std::cout << "Server inited" << std::endl;

    void (*OnReq)(evhttp_request *req, void *) = [](evhttp_request *req, void *) {
        auto *OutBuf = evhttp_request_get_output_buffer(req);
        if (!OutBuf) {
            std::cerr << "evhttp_request_get_output_buffer return NULL" << std::endl;
            return;
        }
        std::stringstream answer;
        answer << "<html><body><center><h1>" << "Hello Wotld! " << strtime02() << "</h1></center></body></html>";
        evbuffer_add_printf(OutBuf, answer.str().c_str());
        evhttp_send_reply(req, HTTP_OK, "", OutBuf);
    };
    evhttp_set_gencb(Server.get(), OnReq, nullptr);

    std::cout << "before event_dispatch" << std::endl;
    if (event_dispatch() == -1) {
        std::cerr << "Failed to run messahe loop." << std::endl;
        return -1;
    }

    std::cout << __func__ << " return 0" << std::endl;
    return 0;
}
